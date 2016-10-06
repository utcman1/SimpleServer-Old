template<typename TSessionHandler>
baAcceptor& ssAcceptor<TSessionHandler>::getBAAcceptor(tSessionPool* _pSessionPool)
{
	return static_cast<baAcceptor&>(static_cast<ssAcceptor&>(*_pSessionPool));
}

template<typename TSessionHandler>
void ssAcceptor<TSessionHandler>::close()
{
	baAcceptor::close();
	tSessionPool::close();
}

template<typename TSessionHandler>
void ssAcceptor<TSessionHandler>::accept(const baEndpoint& _ep)
{
	baAcceptor::open(_ep.protocol());
	baAcceptor::bind(_ep);
	baAcceptor::listen();

	tSessionPool::checkBacklog();
}
