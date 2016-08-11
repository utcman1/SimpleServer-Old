#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



void ssCAcceptor::onError(const BErrorCode& _ec)
{
	std::cerr << _ec.message() << std::endl;
}

void ssCAcceptor::onCompleteAccept(const BErrorCode& _ec, ssCSession& _session)
{
	if (_ec)
	{
		this->onError(_ec);
		m_server.freeSession(&_session);
	}
	else
	{
		_session.issueRecv();
	}
}



ssCAcceptor::ssCAcceptor(ssCService& _server)
	: BAAcceptor(_server), m_server(_server)
{
}

bool ssCAcceptor::init(const BAEndpoint _ep)
{
	BAAcceptor::open(_ep.protocol());
	BAAcceptor::bind(_ep);
	BAAcceptor::listen();

	return this->issueAccept();
}

void ssCAcceptor::release()
{
	BAAcceptor::cancel();
	BAAcceptor::close();
}

bool ssCAcceptor::issueAccept()
{
	ssCSession* psession = m_server.allocSession();
	if (nullptr == psession)
		return false;

	BAAcceptor::async_accept(*psession,
		[this, psession](const BErrorCode& _ec)
		{
			this->onCompleteAccept(_ec, *psession);
		});
	return true;
}
