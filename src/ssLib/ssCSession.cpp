#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



void ssCSession::onError(const BErrorCode& _ec)
{
	std::cerr << _ec.message() << std::endl;
}

void ssCSession::onCompleteRecv(const BErrorCode& _ec, const std::size_t _len)
{
	if (_ec)
	{
		onError(_ec);
	}
	else
	{
		m_recvBuffer.push(_len);

		if (m_recvBuffer.isCompletePacket())
		{
			m_recvBuffer.moveTo(m_sendBuffer);
			issueSend();
		}
		else
		{
			issueRecv();
		}
	}
}

void ssCSession::onCompleteSend(const BErrorCode& _ec, const std::size_t _len)
{
	if (_ec)
	{
		onError(_ec);
	}
	else
	{
		m_sendBuffer.pop(_len);

		if (m_sendBuffer.empty())
		{
			issueRecv();
		}
		else
		{
			issueSend();
		}
	}
}



ssCSession::ssCSession(ssCService& _server)
	: BASocket(_server.getIoService()), m_server(_server)
{
}

void ssCSession::issueRecv()
{
	BASocket::async_read_some(m_recvBuffer.toMutableBuffer(),
		[this](const BErrorCode& _ec, std::size_t _len)
		{
			this->onCompleteRecv(_ec, _len);
		});
}

void ssCSession::issueSend()
{
	BASocket::async_write_some(m_sendBuffer.toConstbuffer(),
		[this](const BErrorCode& _ec, std::size_t _len)
		{
			this->onCompleteSend(_ec, _len);
		});
}
