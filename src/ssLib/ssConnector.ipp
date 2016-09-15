template<typename TSessionHandler>
void ssConnector<TSessionHandler>::connect(const baEndpoint& _ep)
{
	ssSessionPool::issueConnect(_ep);
}
