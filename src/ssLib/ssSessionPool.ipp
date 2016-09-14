template<typename TSessionHandler>
bool ssSessionPool<TSessionHandler>::init(baIoService& _service, const std::size_t _poolSize)
{
	if (!ssSessionPerfCounter::init())
		return false;

	m_free.reserve(_poolSize);
	m_alloc.reserve(_poolSize);

	for (std::size_t i = 0; _poolSize > i; ++i)
	{
		ssSession* pSession = new ssSession(_service, *this);
		if (!pSession->init())
			return false;

		m_free.push_back(pSession);
	}

	return true;
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::release()
{
	assert(0 == m_alloc.size());
	assert(m_free.capacity() == m_free.size());

	for (ssSession* pSession : m_free)
	{
		free(pSession);
	}

	m_free.clear();

	ssSessionPerfCounter::release();
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::close()
{
	for (ssSession* pSession : m_alloc)
	{
		pSession->issueClose();
	}
}



template<typename TSessionHandler>
ssSession<TSessionHandler>* ssSessionPool<TSessionHandler>::alloc()
{
	if (0 == m_free.size())
		return nullptr;

	ssSession* pSession = m_free.back();
	m_free.pop_back();
	pSession->init();
	m_alloc.push_back(pSession);
	return pSession;
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::free(ssSession* _pSession)
{
	erase(m_alloc, _pSession);
	m_free.push_back(_pSession);
}
