template<typename TSessionHandler>
ssSession<TSessionHandler>* ssSessionPool<TSessionHandler>::alloc()
{
	if (0 == m_free.size())
		return nullptr;

	tSession* pSession = m_free.back();
	m_free.pop_back();
	pSession->init();
	m_alloc.push_back(pSession);
	return pSession;
}

template<typename TSessionHandler>
class ssAcceptor;

template<typename TSessionHandler>
class ssConnector;

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::issueBacklog(tSession* _pSession)
{
	++m_backlogSize;

	typedef ssAcceptor<TSessionHandler> tAcceptor;
	typedef ssConnector<TSessionHandler> tConnector;

	switch (m_type)
	{
	case ET_ACCEPT:
		_pSession->issueAccept(tAcceptor::getBAAcceptor(this));
		break;

	case ET_CONNECT:
		_pSession->issueConnect(tConnector::getEndpoint(this));
		break;
	}
}



template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::checkBacklog()
{
	while (m_backlogMaxSize > m_backlogSize)
	{
		tSession* pSession = this->alloc();
		if (nullptr == pSession) return;

		ssSessionPool::issueBacklog(pSession);
	}
}



template<typename TSessionHandler>
bool ssSessionPool<TSessionHandler>::init(const size_t _poolSize, const size_t _backlogMaxSize)
{
	if (!ssSessionPerfCounter::init())
		return false;

	m_poolSize = _poolSize;
	m_backlogMaxSize = _backlogMaxSize;

	m_free.reserve(_poolSize);
	m_alloc.reserve(_poolSize);

	for (std::size_t i = 0; _poolSize > i; ++i)
	{
		tSession* pSession = new tSession(m_ioService, *this);
		if (!pSession->init())
			return false;

		m_free.push_back(pSession);
	}

	return true;
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::release()
{
	assert(0 == m_backlogSize);

	assert(0 == m_alloc.size());
	assert(m_free.capacity() == m_free.size());

	for (tSession* pSession : m_free)
	{
		delete pSession;
	}

	m_free.clear();

	ssSessionPerfCounter::release();
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::close()
{
	for (tSession* pSession : m_alloc)
	{
		pSession->issueClose();
	}
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::free(tSession* _pSession)
{
	// _pSession이 valid한 session ptr이어야 한다.
	assert(m_alloc.end() != std::find(m_alloc.begin(), m_alloc.end(), _pSession));

	erase(m_alloc, _pSession);
	m_free.push_back(_pSession);

	ssSessionPool::checkBacklog();
}

template<typename TSessionHandler>
void ssSessionPool<TSessionHandler>::completeBacklog()
{
	--m_backlogSize;

	ssSessionPool::checkBacklog();
}
