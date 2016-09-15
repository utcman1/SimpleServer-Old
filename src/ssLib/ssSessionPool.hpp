template<typename TSessionHandler>
class ssSessionPool
	: public ssSessionPerfCounter
{
private:
	typedef ssSession<TSessionHandler> ssSession;

private:
	// TODO : 효율적인 pool 구현을 고민해야 한다.
	// 일단은 간단한 모델로 구현한다.
	// boost pool은 고정크기의 pool을 제공하지 않아서 사용하기 좋지 않다.
	std::vector<ssSession*> m_free;
	std::vector<ssSession*> m_alloc;

public:
	bool init(baIoService& _service, const std::size_t _poolSize);
	void release();
	void close();

	ssSession* alloc();
	void free(ssSession* _pSession);

	// accept, connect동작은 session 할당과 같이 이루어지기 때문에
	// session pool에 위치한다.
	void issueAccept(baAcceptor& _acceptor);
	void issueConnect(const baEndpoint& _ep);
};
