template<typename TSessionHandler>
class ssConnector
	: private ssSessionPool<TSessionHandler>
{
private:
	typedef ssSessionPool<TSessionHandler> ssSessionPool;

private:
	baEndpoint m_ep;

private:
	// delete copy constructor, assignment operator
	ssConnector(const ssConnector&) = delete;
	ssConnector& operator=(const ssConnector&) = delete;

public:
	ssConnector()
		: ssSessionPool(ssSessionPool::ET_CONNECT) {}

	const baEndpoint& getEndpoint() const { return m_ep; }

	// 인터페이스 노출
	using ssSessionPool::init;
	using ssSessionPool::release;
	using ssSessionPool::close;

	void connect(const baEndpoint& _ep);
};
