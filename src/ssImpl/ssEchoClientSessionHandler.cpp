#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoClientSessionHandler.hpp>



void ssEchoClientSessionHandler::onConnect()
{
	// 첫번째 메시지 전송은 "클라 => 서버" 이다.
	m_sendBuffer.push("A", 1);
	ssSession::issueSend();
}

void ssEchoClientSessionHandler::onRecv(const std::size_t _len)
{
	m_recvBuffer.completePush(_len);

	if (0 < m_recvBuffer.size())
	{
		m_sendBuffer.push(m_recvBuffer);
		ssSession::issueSend();
	}
	else
	{
		ssSession::issueRecv();
	}
}

void ssEchoClientSessionHandler::onSend(const std::size_t _len)
{
	m_sendBuffer.completePop(_len);

	if (m_sendBuffer.empty())
	{
		ssSession::issueRecv();
	}
	else
	{
		ssSession::issueSend();
	}
}
