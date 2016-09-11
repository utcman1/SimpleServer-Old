template<typename TSessionHandler>
ssSessionPool<TSessionHandler>::ssSessionPool(baIoService& _service, const int _poolSize)
{
	m_poolSession.reserve(_poolSize);

	for (int i = 0; _poolSize > i; ++i)
	{
		m_poolSession.push_back(new ssSession(_service, *this));
	}
}

template<typename TSessionHandler>
bool ssSessionPool<TSessionHandler>::init()
{
	for (ssSession* pSession : m_poolSession)
	{
		if (!pSession->init())
			return false;
	}

	return true;
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::release()
{
	// 풀에 모두 반납된 상태에서 release() 호출해야 한다.
	assert(m_poolSession.capacity() == m_poolSession.size());
}

template<typename TSessionHandler>
ssSession<TSessionHandler>* ssSessionPool<TSessionHandler>::alloc()
{
	return (0 == m_poolSession.size()) ? nullptr : m_poolSession.pop_back();
}


template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::free(ssSession* _psession)
{
	m_poolSession.push_back(_psession);
}
