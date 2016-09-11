#include <stdafx.hpp>
#include <ssLib.hpp>



void ssAcceptor::onError(const bsErrorCode& _ec)
{
	std::cerr << _ec.message() << std::endl;
}

void ssAcceptor::onCompleteAccept(const bsErrorCode& _ec, ssSession& _session)
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



ssAcceptor::ssAcceptor(baIoService& _service)
	: baAcceptor(_service)
{
}

bool ssAcceptor::init(const baEndpoint _ep)
{
	baAcceptor::open(_ep.protocol());
	baAcceptor::bind(_ep);
	baAcceptor::listen();

	return this->issueAccept();
}

void ssAcceptor::release()
{
	baAcceptor::cancel();
	baAcceptor::close();
}

bool ssAcceptor::issueAccept()
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
