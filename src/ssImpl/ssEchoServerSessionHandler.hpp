class ssEchoServerSessionHandler
	: public ssSession<ssEchoServerSessionHandler>
{
public:
	void onTick();
	void onError(const bsErrorCode& _ec);
	void onCompleteRecv(const bsErrorCode& _ec, const std::size_t _len);
	void onCompleteSend(const bsErrorCode& _ec, const std::size_t _len);
	void onCompleteConnect(const bsErrorCode& _ec);
};
