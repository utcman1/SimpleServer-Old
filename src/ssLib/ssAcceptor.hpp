template<typename TSessionHandler>
class ssAcceptor
	: private baAcceptor, private ssSessionPool<TSessionHandler>
{
private:
	typedef ssSessionPool<TSessionHandler> tSessionPool;

private:
	// delete copy constructor, assignment operator
	ssAcceptor(const ssAcceptor&) = delete;
	ssAcceptor& operator=(const ssAcceptor&) = delete;

public:
	ssAcceptor(baIoService& _ioService)
		: baAcceptor(_ioService), tSessionPool(_ioService, tSessionPool::ET_ACCEPT)
	{}

	baAcceptor& getBAAcceptor() { return static_cast<baAcceptor&>(*this); }

	// 인터페이스 노출
	using tSessionPool::init;
	using tSessionPool::release;

	void close();
	void accept(const baEndpoint& _ep);		// throw accept exception
};
