class ssCService
	: public BAIoService
{
private:
	ssCAcceptor m_acceptor;
	ssCSession m_session;

public:
	ssCService();

	ssCSession* allocSession();
	void freeSession(ssCSession* _psession);

	void accept(const BAEndpoint _ep);
	void connect(const BAEndpoint _ep);
};
