class ssService
	: public baIoService
{
private:
	ssAcceptor m_acceptor;
	ssSession m_session;

public:
	ssService();

	ssSession* allocSession();
	void freeSession(ssSession* _psession);

	void accept(const baEndpoint _ep);
	void connect(const baEndpoint _ep);
};
