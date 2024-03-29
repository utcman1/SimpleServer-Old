﻿template<typename TSessionHandler>
class ssSessionPool
	: public ssSessionPerfCounter
{
private:
	typedef std::size_t size_t;
	typedef ssSession<TSessionHandler> tSession;

protected:
	enum EType : uint8_t
	{
		ET_ACCEPT,
		ET_CONNECT
	} m_type;

private:
	baIoService& m_ioService;
	size_t m_poolSize = 0;
	size_t m_backlogMaxSize = 0;
	size_t m_backlogSize = 0;

	// TODO : 효율적인 pool 구현을 고민해야 한다.
	// 일단은 간단한 모델로 구현한다.
	// boost pool은 고정크기의 pool을 제공하지 않아서 사용하기 좋지 않다.
	std::vector<tSession*> m_free;
	std::vector<tSession*> m_alloc;

private:
	// delete copy constructor, assignment operator
	ssSessionPool(const ssSessionPool&) = delete;
	ssSessionPool& operator=(const ssSessionPool&) = delete;

private:
	tSession* alloc();
	void issueBacklog(tSession* _pSession);

protected:
	void checkBacklog();

public:
	ssSessionPool(baIoService& _ioService, const EType _type)
		: ssSessionPerfCounter(_ioService), m_type(_type), m_ioService(_ioService) {}

	bool init(const size_t _poolSize, const size_t _backlogMaxSize);
	void release();
	void close();

	void free(tSession* _pSession);
	void completeBacklog();
};
