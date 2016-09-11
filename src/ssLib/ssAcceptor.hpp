template<typename TSessionHandler>
class ssAcceptor
	: private baAcceptor
{
private:
	ssSessionPool			m_sessionPool;
	ssSessionPerfCounter	m_sessionPerfCounter;

public:
	ssAcceptor(baIoService& _service)
		: baAcceptor(_service)
	{}

	bool init(const int _poolSize)
	{
		return	(m_sessionPool.init(_poolSize)) &&
				(m_sessionPerfCounter.init());
	}

	void release()
	{
		m_sessionPool.release();
		m_sessionPerfCounter.release();
	}



	bool prepareAccept(const baEndpoint _ep)
	{
		baAcceptor::open(_ep.protocol());
		baAcceptor::bind(_ep);
		baAcceptor::listen();
	}

	bool issueAccept()
	{
		ssSession* psession = m_server.allocSession();
		if (nullptr == psession)
			return false;

		baAcceptor::async_accept(*psession,
			[this, psession](const bsErrorCode& _ec)
		{
			this->onCompleteAccept(_ec, *psession);
		});
		return true;
	}

	void cancelAccept()
	{
		baAcceptor::cancel();
		baAcceptor::close();
	}
};
