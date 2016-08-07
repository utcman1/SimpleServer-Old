class ssCService
{
private:
	BAIoService m_ioService;
	ssCAcceptor m_acceptor;
	ssCSession m_session;

public:
	ssCService()
		: m_acceptor(*this), m_session(*this) {}

	BAIoService& getIoService() { return m_ioService; }
	void accept(const unsigned short _port)
	{
		m_acceptor.bind(BAEndpoint(BATcp::v4(), _port));
		m_acceptor.issueAccept();
	}
	void run() { m_ioService.run(); }
	ssCSession* allocSession() { return &m_session; }
	void freeSession(ssCSession* _psession) {}
};
