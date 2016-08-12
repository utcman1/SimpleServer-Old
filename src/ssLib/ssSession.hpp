class ssService;



// TODO : 효율적인 pooling을 위해서는 move constructor & move assignment operator를 정의해야 한다.
class ssSession
	: public baSocket
{
private:
	ssService& m_server;
	ssBuffer m_recvBuffer;
	ssBuffer m_sendBuffer;

private:
	// TODO : 현재는 임시 구현이다. 정식 구현에서는 외부에서 핸들러를 받아야 한다.
	void onError(const bsErrorCode& _ec);
	void onCompleteRecv(const bsErrorCode& _ec, const std::size_t _len);
	void onCompleteSend(const bsErrorCode& _ec, const std::size_t _len);
	void onCompleteConnect(const bsErrorCode& _ec);

public:
	ssSession(ssService& _server);

	bool init();
	void release();

	void issueRecv();
	void issueSend();
	void issueConnect(const baEndpoint _ep);
};
