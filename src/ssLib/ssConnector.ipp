template<typename TSessionHandler>
void ssConnector<TSessionHandler>::connect(const baEndpoint& _ep)
{
	m_ep = _ep;

	ssSessionPool::checkBacklog();
}
