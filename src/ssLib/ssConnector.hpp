template<typename TSessionHandler>
class ssConnector
	: private ssSessionPool<TSessionHandler>
{
private:
	typedef ssSessionPool<TSessionHandler> tSessionPool;

private:
	baEndpoint m_ep;

private:
	// delete copy constructor, assignment operator
	ssConnector(const ssConnector&) = delete;
	ssConnector& operator=(const ssConnector&) = delete;

public:
	ssConnector(baIoService& _ioService)
		: tSessionPool(_ioService, tSessionPool::ET_CONNECT) {}

	const baEndpoint& getEndpoint() const { return m_ep; }

	// 인터페이스 노출
	using tSessionPool::init;
	using tSessionPool::release;
	using tSessionPool::close;

	void connect(const baEndpoint& _ep);
};
