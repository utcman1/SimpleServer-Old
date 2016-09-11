template<typename TSessionHandler>
void ssSession<TSessionHandler>::log(const std::string& _msg)
{
	std::cerr << _msg << std::endl;
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::release()
{
	sessionHandler().onRelease();
	m_sessionPool.free(this);
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::releaseIfNeed()
{
	if (!this->m_bPandingClose) return;
	if (this->m_bPendingConnect || this->m_bPendingRecv || this->m_bPendingSend) return;

	// close가 진행중이고, pending중인 작업이 없으면 relese를 호출한다.
	this->release();
}



template<typename TSessionHandler>
void ssSession<TSessionHandler>::onError(const bsErrorCode& _ec)
{
	ssSession::log(_ec.message());
	ssSession::issueClose();
}



template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueClose()
{
	if (m_bPendingClose)
	{
		ssSession::log("Ignore issueClose() call on PendingClose session");
		return;
	}

	m_bPendingClose = true;
	baSocket::close();
	sessionHandler().onClosing();
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueConnect(const baEndpoint _ep)
{
	if (m_bPendingClose)
	{
		ssSession::log("Ignore issueConnect() call on PendingClose session");
		return;
	}

	if (m_bPendingConnect)
	{
		ssSession::log("Ignore issueConnect() call on PendingConnect session");
		return;
	}

	this->m_bPendingConnect = true;
	baSocket::async_connect(_ep,
		[this](const bsErrorCode& _ec)
		{
			this->m_bPendingConnect = false;
			TSessionHandler& handler = this->sessionHandler();

			if (_ec)
			{
				handler.onConnectError(_ec);
			}
			else
			{
				handler.onConnect();
			}

			this->releaseIfNeed();
		});
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueRecv()
{
	if (m_bPendingClose)
	{
		ssSession::log("Ignore issueRecv() call on PendingClose session");
		return;
	}

	if (m_bPendingRecv)
	{
		ssSession::log("Ignore issueRecv() call on PendingRecv session");
		return;
	}

	this->m_bPendingRecv = true;
	baSocket::async_read_some(m_recvBuffer.toMutableBuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			this->m_bPendingRecv = false;
			TSessionHandler& handler = this->sessionHandler();
			if (_ec)
			{
				handler.onRecvError(_ec);
			}
			else
			{
				handler.onRecv(_len);
			}

			this->releaseIfNeed();
		});
}

template<typename TSessionHandler>
void ssSession<TSessionHandler>::issueSend()
{
	if (m_bPendingClose)
	{
		ssSession::log("Ignore issueSend() call on PendingClose session");
		return;
	}

	if (m_bPendingSend)
	{
		ssSession::log("Ignore issueSend() call on PendingSend session");
		return;
	}

	this->m_bPendingSend = true;
	baSocket::async_write_some(m_sendBuffer.toConstbuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			this->m_bPendingSend = false;
			TSessionHandler& handler = this->sessionHandler();
			if (_ec)
			{
				handler.onSendError(_ec);
			}
			else
			{
				handler.onSend(_len);
			}

			this->releaseIfNeed();
		});
}
