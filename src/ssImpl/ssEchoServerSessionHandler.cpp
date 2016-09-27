#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoServerSessionHandler.hpp>



void ssEchoServerSessionHandler::onAccept()
{
	// 첫번째 메시지 전송은 "클라 => 서버" 이다.
	tSession::issueRecv();
}

void ssEchoServerSessionHandler::onRecv(const std::size_t _len)
{
	m_recvBuffer.completePush(_len);

	if (0 < m_recvBuffer.size())
	{
		m_sendBuffer.push(m_recvBuffer);
		tSession::issueSend();
	}
	else
	{
		tSession::issueRecv();
	}
}

void ssEchoServerSessionHandler::onSend(const std::size_t _len)
{
	m_sendBuffer.completePop(_len);

	if (m_sendBuffer.empty())
	{
		tSession::issueRecv();
	}
	else
	{
		tSession::issueSend();
	}
}
