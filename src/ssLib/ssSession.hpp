template<typename TSessionHandler>
class ssSessionPool;



// TODO : 효율적인 pooling을 위해서는 move constructor & move assignment operator를 정의해야 한다.
template<typename TSessionHandler>
class ssSession
	: private baSocket
{
private:
	typedef ssSessionPool<TSessionHandler> ssSessionPool;

protected:
	// TSessionHandler에서 api를 통한 버퍼 접근 권한이 필요하다.
	ssBuffer		m_recvBuffer;
	ssBuffer		m_sendBuffer;

private:
	ssSessionPool&	m_sessionPool;

	enum EState : uint8_t
	{
		ES_CLOSED,
		ES_PENDING_CONNECT,		// connect 진행중
		ES_PENDING_ACCEPT,		// accept 대기중
		ES_ESTABLISHED			// 연결된 상태 recv / send 가 가능하다.
	} m_state = ES_CLOSED;

	// pendingClose 상태는 ESTABLISHED가 아닌 상태에서도 호출이 가능하기 때문에 EState에 통합할수 없다.
	// close 요청시 pending 중인 요청을 기다리는 과정이 필요하다.
	// issueClose() => wait for idle => onRelease() 순으로 진행한다.
	// issueClose() 이후의 모든 issue는 거부된다.
	bool m_bPendingClose = false;

	// recv, send는 동시에 각각 1개의 operation만 진행한다. ES_ESTABLISHED 상태에서만 가능하다.
	// 구현을 간편하게 하기 위해 EState에 통합하지 않고 별도의 flag로 구현했다.
	bool m_bPendingRecv = false;
	bool m_bPendingSend = false;



private:
	// delete copy constructor, assignment operator
	ssSession(const ssSession&) = delete;
	ssSession& operator=(const ssSession&) = delete;

private:
	TSessionHandler& sessionHandler() { return static_cast<TSessionHandler&>(*this); }
	bool isIdle() { return (!m_bPendingClose && !m_bPendingRecv && !m_bPendingSend); }

	// release()는 CLOSED 상태일때만 호출한다.
	void release();

	// 세션이 사용중인 상태에서 release()를 호출하는 경우 issue중인 동작이 꼬이는 문제가 발생한다. 
	// close 과정이 완료된 이후에 release()를 진행한다.
	void completeClose();



private:
	//////////////////////////////////////////////////////////////////////////////
	// callback interface
	// onXXX 코드는 TSessionHandler 클래스에서 override 한다.
	// Life cycle : onInit -> (onConnect/onAccept) -> (onRecv/onSend) ... -> onClosing -> wait for idle -> onRelease
	bool onInit() { return true; }
	void onRelease() {}

	// 기본 Error Handler. 각 ErrorHandler의 기본 구현은 이 함수를 호출하도록 되어 있다.
	void onError(const bsErrorCode& _ec);

	// close 과정 시작. 아직 close가 완료된 것은 아니다.
	// issueClose()를 호출하는 경우에는 굳이 필요하지 않지만, 에러로 세션이 종료되는 경우를 위해 필요하다.
	void onClosing() {}

	void onConnect() {}
	void onConnectError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }

	// accept완료 이후 생성된 socket에서 호출됨
	void onAccept() {}
	void onAcceptError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }


	void onRecv(const std::size_t _len);
	void onRecvError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }
	void onSend(const std::size_t _len);
	void onSendError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }
	// callback interface
	//////////////////////////////////////////////////////////////////////////////



public:
	ssSession(baIoService& _service, ssSessionPool& _sessionPool)
		: baSocket(_service), m_sessionPool(_sessionPool) {}

	bool init() { return sessionHandler().onInit(); }

	void issueClose();
	void issueConnect(const baEndpoint _ep);

	// acceptor의 기능이지만 session 내부 구현에 매우 종속적이기 때문에 이곳에 구현한다.
	// 설계 측면에서도 나쁘지 않다.
	void issueAccept(baAcceptor& _acceptor);

	void issueRecv();
	void issueSend();
};
