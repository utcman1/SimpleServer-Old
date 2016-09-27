class ssEchoClientSessionHandler final
	: public ssSession<ssEchoClientSessionHandler>
{
private:
	typedef ssSession<ssEchoClientSessionHandler> tSession;

private:
	// constructor
	ssEchoClientSessionHandler() = delete;
	~ssEchoClientSessionHandler() = delete;

	// copy constructor, assignment operator
	ssEchoClientSessionHandler(const ssEchoClientSessionHandler&) = delete;
	ssEchoClientSessionHandler& operator=(const ssEchoClientSessionHandler&) = delete;

public:
	void onConnect();
	void onRecv(const std::size_t _len);
	void onSend(const std::size_t _len);
};
