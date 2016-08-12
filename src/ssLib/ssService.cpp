#include <stdafx.hpp>
#include <ssLib.hpp>



ssService::ssService()
	: m_acceptor(*this), m_session(*this)
{
}

ssSession* ssService::allocSession()
{
	return &m_session;
}

void ssService::freeSession(ssSession* _psession)
{
}

void ssService::accept(const baEndpoint _ep)
{
	m_acceptor.init(_ep);
}

void ssService::connect(const baEndpoint _ep)
{
	m_session.issueConnect(_ep);
}
