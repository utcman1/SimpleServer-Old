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
	// TODO : 현재는 임시 구현이다. 정식 구현에서는 외부에서 핸들러를 받아야 한다.
	void onError(const BErrorCode& _ec);
	void onCompleteRecv(const BErrorCode& _ec, const std::size_t _len);
	void onCompleteSend(const BErrorCode& _ec, const std::size_t _len);
	void onCompleteConnect(const BErrorCode& _ec);

public:
	ssCSession(ssCService& _server);

	bool init();
	void release();

	void issueRecv();
	void issueSend();
	void issueConnect(const BAEndpoint _ep);
};
