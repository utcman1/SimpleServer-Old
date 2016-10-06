template<typename TSessionHandler>
const baEndpoint& ssConnector<TSessionHandler>::getEndpoint(tSessionPool* _pSessionPool)
{
	return static_cast<ssConnector*>(_pSessionPool)->m_ep;
}

template<typename TSessionHandler>
void ssConnector<TSessionHandler>::connect(const baEndpoint& _ep)
{
	m_ep = _ep;

	tSessionPool::checkBacklog();
}
