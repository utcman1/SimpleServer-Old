class ssEchoServerSessionHandler final
	: public ssSession<ssEchoServerSessionHandler>
{
private:
	typedef ssSession<ssEchoServerSessionHandler> tSession;

private:
	// constructor
	ssEchoServerSessionHandler() = delete;
	~ssEchoServerSessionHandler() = delete;

	// copy constructor, assignment operator
	ssEchoServerSessionHandler(const ssEchoServerSessionHandler&) = delete;
	ssEchoServerSessionHandler& operator=(const ssEchoServerSessionHandler&) = delete;

public:
	void onAccept();
	void onRecv(const std::size_t _len);
	void onSend(const std::size_t _len);
};
