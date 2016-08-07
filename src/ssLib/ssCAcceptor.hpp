class ssCService;
class ssCSession;



class ssCAcceptor
	: public BAAcceptor
{
private:
	ssCService& m_server;

private:
	void onError(const BErrorCode& _ec);
	void onCompleteAccept(const BErrorCode& _ec, ssCSession& _session);

public:
	ssCAcceptor(ssCService& _server);

	bool issueAccept();
};
