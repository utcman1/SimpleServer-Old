template<typename TSessionHandler>
class ssAcceptor
	: private baAcceptor, private ssSessionPool<TSessionHandler>
{
private:
	typedef ssSessionPool<TSessionHandler> ssSessionPool;

private:
	// delete copy constructor, assignment operator
	ssAcceptor(const ssAcceptor&) = delete;
	ssAcceptor& operator=(const ssAcceptor&) = delete;

public:
	ssAcceptor(baIoService& _service)
		: baAcceptor(_service), ssSessionPool(ssSessionPool::ET_ACCEPT)
	{}

	baAcceptor& getBAAcceptor() { return static_cast<baAcceptor&>(*this); }

	// 인터페이스 노출
	using ssSessionPool::init;
	using ssSessionPool::release;

	void close();
	void accept(const baEndpoint& _ep);		// throw accept exception
};
