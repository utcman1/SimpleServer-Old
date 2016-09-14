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
		: baAcceptor(_service)
	{}

	// init, release 인터페이스 노출
	using ssSessionPool::init;
	using ssSessionPool::release;

	void accept(const baEndpoint& _ep);		// throw accept exception
	void close();
};
