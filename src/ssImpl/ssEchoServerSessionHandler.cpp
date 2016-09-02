#include <stdafx.hpp>
#include <ssLib.hpp>
#include <ssImpl/ssEchoServerSessionHandler.hpp>



void ssEchoServerSessionHandler::onError(const bsErrorCode& _ec)
{
	std::cerr << _ec.message() << std::endl;
}

void ssEchoServerSessionHandler::onCompleteRecv(const bsErrorCode& _ec, const std::size_t _len)
{
	if (_ec)
	{
		this->onError(_ec);
	}
	else
	{
		ssSessionPerfCounter::onRecv();

		m_recvBuffer.push(_len);

		if (m_recvBuffer.isCompletePacket())
		{
			m_recvBuffer.moveTo(m_sendBuffer);
			this->issueSend();
		}
		else
		{
			this->issueRecv();
		}
	}
}

void ssEchoServerSessionHandler::onCompleteSend(const bsErrorCode& _ec, const std::size_t _len)
{
	if (_ec)
	{
		this->onError(_ec);
	}
	else
	{
		m_sendBuffer.pop(_len);

		if (m_sendBuffer.empty())
		{
			this->issueRecv();
		}
		else
		{
			this->issueSend();
		}
	}
}

void ssEchoServerSessionHandler::onCompleteConnect(const bsErrorCode& _ec)
{
	if (_ec)
	{
		this->onError(_ec);
	}
	else
	{
		// TODO : connect 성공하면 echo send를 시작한다. 이건 임시 구현이다.
		m_sendBuffer.push(1);
		this->issueSend();
	}
}
