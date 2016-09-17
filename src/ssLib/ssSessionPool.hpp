template<typename TSessionHandler>
class ssSessionPool
	: public ssSessionPerfCounter
{
private:
	typedef std::size_t size_t;
	typedef ssSession<TSessionHandler> ssSession;

protected:
	enum EType : uint8_t
	{
		ET_ACCEPT,
		ET_CONNECT
	} m_type;

private:
	size_t m_poolSize;
	size_t m_backlogMaxSize;
	size_t m_backlogSize = 0;

	// TODO : 효율적인 pool 구현을 고민해야 한다.
	// 일단은 간단한 모델로 구현한다.
	// boost pool은 고정크기의 pool을 제공하지 않아서 사용하기 좋지 않다.
	std::vector<ssSession*> m_free;
	std::vector<ssSession*> m_alloc;

public:
	ssSessionPool(const EType _type)
		: m_type(_type) {}

	bool init(baIoService& _service, const size_t _poolSize, const size_t _backlogMaxSize);
	void release();
	void close();

	ssSession* alloc();
	void free(ssSession* _pSession);

	void incBacklog() { ++m_backlogSize; }
	void decBacklog() { --m_backlogSize; }
	void checkBacklog();
};
