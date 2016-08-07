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
		onError(_ec);
		m_server.freeSession(&_session);
	}
	else
	{
		_session.issueRecv();
	}
}



ssCAcceptor::ssCAcceptor(ssCService& _server)
	: BAAcceptor(_server.getIoService()), m_server(_server)
{
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
