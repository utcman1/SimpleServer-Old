class ssService;



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
	ssSessionPool(ssService& _service, const int _poolSize)
	{
		m_poolSession.reserve(_poolSize);

		for (int i = 0; _poolSize > i; ++i)
		{
			m_poolSession.push_back(new ssSession(ssService& _service, *this));
		}
	}

	ssSession* alloc()
	{
		return (0 == m_poolSession.size()) ? nullptr : m_poolSession.pop_back();
	}

	void free(ssSession* _psession)
	{
		m_poolSession.push_back(_psession);
	}
};
