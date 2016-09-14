template<typename TSessionHandler>
void ssAcceptor<TSessionHandler>::accept(const baEndpoint& _ep)
{
	baAcceptor::open(_ep.protocol());
	baAcceptor::bind(_ep);
	baAcceptor::listen();

	ssSessionPool::alloc()->issueAccept(*this);
}

template<typename TSessionHandler>
void ssAcceptor<TSessionHandler>::close()
{
	baAcceptor::close();
	ssSessionPool::close();
}
