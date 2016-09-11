template<typename TSessionHandler>
class ssSessionPool
{
	typedef ssSession<TSessionHandler> ssSession;

private:
	// TODO : 효율적인 pool 구현을 고민해야 한다.
	// 일단은 간단한 모델로 구현한다.
	// boost pool은 고정크기의 pool을 제공하지 않아서 사용하기 좋지 않다.
	std::vector<ssSession*> m_poolSession;

public:
	ssSessionPool(baIoService& _service, const int _poolSize);

	bool init();
	// TODO : release는 이렇게 작성하지 말고
	// callback 형태로 작성해야 한다.
	void release();

	ssSession* alloc();
	void free(ssSession* _psession);
};
