class ssCService;



// TODO : 효율적인 pooling을 위해서는 move constructor & move assignment operator를 정의해야 한다.
class ssCSession
	: public BASocket
{
private:
	ssCService& m_server;
	ssCBuffer m_recvBuffer;
	ssCBuffer m_sendBuffer;

private:
	void onError(const BErrorCode& _ec);
	void onCompleteRecv(const BErrorCode& _ec, const std::size_t _len);
	void onCompleteSend(const BErrorCode& _ec, const std::size_t _len);

public:
	ssCSession(ssCService& _server);

	void issueRecv();
	void issueSend();
};
