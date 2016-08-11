class ssCService;
class ssCSession;



class ssCAcceptor
	: public BAAcceptor
{
private:
	ssCService& m_server;

private:
	// TODO : 현재는 임시 구현이다. 정식 구현에서는 외부에서 핸들러를 받아야 한다.
	void onError(const BErrorCode& _ec);
	void onCompleteAccept(const BErrorCode& _ec, ssCSession& _session);

public:
	ssCAcceptor(ssCService& _server);

	bool init(const BAEndpoint _ep);
	void release();

	bool issueAccept();
};
