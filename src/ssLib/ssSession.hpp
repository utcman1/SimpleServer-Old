template<typename TSessionHandler>
class ssSessionPool;



// TODO : 효율적인 pooling을 위해서는 move constructor & move assignment operator를 정의해야 한다.
template<typename TSessionHandler>
class ssSession
	: private baSocket
{
protected:
	ssSessionPool<TSessionHandler>& m_sessionPool;

	// close 요청시 pending 중인 요청을 기다리는 과정이 필요하다.
	// issueClose() => onClosing() => wait for idle => onRelease() 순으로 진행한다.
	// issueClose() 이후의 모든 issue는 거부된다.
	bool m_bPendingClose = false;

	// connect, recv, send는 동시에 1개의 operation만 진행한다.
	bool m_bPendingConnect = false;
	bool m_bPendingRecv = false;
	bool m_bPendingSend = false;

	ssBuffer m_recvBuffer;
	ssBuffer m_sendBuffer;



private:
	void log(const std::string& _msg);
	TSessionHandler& sessionHandler() { return staic_cast<TSessionHandler&>(*this); }

	// 세션이 사용중인 상태에서 release()를 호출하는 경우 issue중인 동작이
	// 꼬이는 문제가 발생한다. release()는 반드시 issue중인 작업이 완료된
	// 상태에서만 호출되어야 한다.
	// issueClose()를 호출해서 자동으로 onRelease()를 호출받도록 설계한다.
	void release();
	void releaseIfNeed();



	//////////////////////////////////////////////////////////////////////////////
	// callback interface
	// onXXX 코드는 TSessionHandler 클래스에서 override 한다.
	// Life cycle : onInit -> (onConnect/onAccept) -> (onRecv/onSend) ... -> onClosing -> wait for idle -> onRelease
	bool onInit() {}
	void onRelease() {}

	// 기본 Error Handler. 각 ErrorHandler의 기본 구현은 이 함수를 호출하도록 되어 있다.
	void onError(const bsErrorCode& _ec);

	// close 과정 시작. 아직 close가 완료된 것은 아니다.
	void onClosing() {}

	void onConnect() {}
	void onConnectError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }

	// accept완료 이후 생성된 socket에서 호출됨
	// acceptor에서 에러 발생한 경우에는 SessionHandler가 아닌 AcceptorHandler에서 처리한다.
	void onAccept() {}


	void onRecv(const std::size_t _len) {}
	void onRecvError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }
	void onSend(const std::size_t _len) {}
	void onSendError(const bsErrorCode& _ec) { sessionHandler().onError(_ec); }
	// callback interface
	//////////////////////////////////////////////////////////////////////////////



public:
	ssSession(baIoService& _service, ssSessionPool<TSessionHandler>& _sessionPool)
		: baSocket(_service), m_sessionPool(_sessionPool) {}

	bool init() { return sessionHandler().onInit(); }

	void issueClose();
	void issueConnect(const baEndpoint _ep);

	void issueRecv();
	void issueSend();
};
