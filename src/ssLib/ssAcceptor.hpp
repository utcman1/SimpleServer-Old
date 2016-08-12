class ssService;
class ssSession;



class ssAcceptor
	: public baAcceptor
{
private:
	ssService& m_server;

private:
	// TODO : 현재는 임시 구현이다. 정식 구현에서는 외부에서 핸들러를 받아야 한다.
	void onError(const bsErrorCode& _ec);
	void onCompleteAccept(const bsErrorCode& _ec, ssSession& _session);

public:
	ssAcceptor(ssService& _server);

	bool init(const baEndpoint _ep);
	void release();

	bool issueAccept();
};
