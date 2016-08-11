#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



ssCService::ssCService()
	: m_acceptor(*this), m_session(*this)
{
}

ssCSession* ssCService::allocSession()
{
	return &m_session;
}

void ssCService::freeSession(ssCSession* _psession)
{
}

void ssCService::accept(const BAEndpoint _ep)
{
	m_acceptor.init(_ep);
}

void ssCService::connect(const BAEndpoint _ep)
{
	m_session.issueConnect(_ep);
}
