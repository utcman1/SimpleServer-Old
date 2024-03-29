﻿template<typename TSessionHandler>
void ssSession<TSessionHandler>::release()
{
	// CLOSED 상태의 세션만 release가 가능하다.
	assert(ES_CLOSED == m_state);
	assert(ssSession::isIdle());

	// 코드가 대칭을 이루지 못해 안이쁘긴 하지만.
	// sessionPool::alloc() & session::init() 호출 코드는 sessionPool::alloc()에
	// session::release() & sessionPool::free() 호출 코드는 session::release()에
	// 위치하는 것이 맞다.
	// 세션 생성 시점에는 외부에서 세션풀을 통한 할당으로 처리
	// 세션의 소멸 시점에는 세션 자체에서 수명주기 관리를 통한 처리
	sessionHandler().onRelease();
	m_sessionPool.free(this);
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::checkCloseComplete()
{
	// 이 함수는 실제 close가 진행중이 아닌 상태에서도 호출하기 때문에 assert로 검사하지 않는다.
	if (!m_bPendingClose) return;

	// ES_CLOSED 상태에서 checkCloseComplete()를 진행하는게 좀 이상하지만,
	// ES_PENDING_CONNECT/ES_PENDING_ACCEPT 상태에서 issueClose()를 진행하면
	// ES_ESTABLISHED 상태로 진입하지 않고 바로 ES_CLOSED 상태로 진행한다.
	if (ES_CLOSED != m_state && ES_ESTABLISHED != m_state) return;
	if (m_bPendingRecv || m_bPendingSend) return;

	// complete close
	m_bPendingClose = false;
	m_state = ES_CLOSED;

	ssSession::release();
}



template<typename TSessionHandler>
void ssSession<TSessionHandler>::onError(const bsErrorCode& _ec)
{
	ssWARNING << _ec.message();
}



template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueClose()
{
	// TODO : 2가지 이상의 요청이 동시에 pending된 경우
	// 아래 assert 문은 안전한가?
	// ex) recv / send 동시에 진행중 close된 경우
	//		error가 2번 전파된다.
	assert(ES_CLOSED != m_state);
	assert(!m_bPendingClose);

	m_bPendingClose = true;
	m_socket.close();
	sessionHandler().onClosing();
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueAccept(baAcceptor& _acceptor)
{
	assert(ES_CLOSED == m_state);
	assert(isIdle());

	m_state = ES_PENDING_ACCEPT;
	_acceptor.async_accept(m_socket,
		[this](const bsErrorCode& _ec)
		{
			TSessionHandler& handler = this->sessionHandler();

			if (_ec)
			{
				handler.onAcceptError(_ec);
				ssSession::issueClose();
			}
			else
			{
				this->m_state = ES_ESTABLISHED;
				this->m_sessionPool.countAccept();
				handler.onAccept();
			}

			this->checkCloseComplete();
			m_sessionPool.completeBacklog();
		});
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueConnect(const baEndpoint& _ep)
{
	assert(ES_CLOSED == m_state);
	assert(ssSession::isIdle());

	m_state = ES_PENDING_CONNECT;
	m_socket.async_connect(_ep,
		[this](const bsErrorCode& _ec)
		{
			TSessionHandler& handler = this->sessionHandler();

			if (_ec)
			{
				handler.onConnectError(_ec);
				ssSession::issueClose();
			}
			else
			{
				this->m_state = ES_ESTABLISHED;
				this->m_sessionPool.countConnect();
				handler.onConnect();
			}

			this->checkCloseComplete();
			m_sessionPool.completeBacklog();
		});
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueRecv()
{
	assert(ES_ESTABLISHED == m_state);

	if (m_bPendingClose)
	{
		ssERROR << "Ignore issueRecv() call : PendingClose";
		return;
	}

	if (m_bPendingRecv)
	{
		ssERROR << "Ignore issueRecv() call : PendingRecv";
		return;
	}

	m_bPendingRecv = true;
	m_socket.async_read_some(m_recvBuffer.toMutableBuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			m_bPendingRecv = false;
			TSessionHandler& handler = this->sessionHandler();

			if (_ec)
			{
				handler.onRecvError(_ec);
				ssSession::issueClose();
			}
			else
			{
				this->m_sessionPool.countRecv();
				handler.onRecv(_len);
			}

			this->checkCloseComplete();
		});
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueSend()
{
	assert(ES_ESTABLISHED == m_state);

	if (m_bPendingClose)
	{
		ssERROR << "Ignore issueSend() call : PendingClose";
		return;
	}

	if (m_bPendingSend)
	{
		ssERROR << "Ignore issueSend() call : PendingSend";
		return;
	}

	m_bPendingSend = true;
	m_socket.async_write_some(m_sendBuffer.toConstbuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			m_bPendingSend = false;
			TSessionHandler& handler = this->sessionHandler();

			if (_ec)
			{
				handler.onSendError(_ec);
				ssSession::issueClose();
			}
			else
			{
				this->m_sessionPool.countSend();
				handler.onSend(_len);
			}

			this->checkCloseComplete();
		});
}
