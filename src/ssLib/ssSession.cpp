#include <stdafx.hpp>
#include <ssLib.hpp>



void ssSession::onError(const bsErrorCode& _ec)
{
	std::cerr << _ec.message() << std::endl;
}

void ssSession::onCompleteRecv(const bsErrorCode& _ec, const std::size_t _len)
{
	if (_ec)
	{
		this->onError(_ec);
	}
	else
	{
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

void ssSession::onCompleteSend(const bsErrorCode& _ec, const std::size_t _len)
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

void ssSession::onCompleteConnect(const bsErrorCode& _ec)
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



ssSession::ssSession(ssService& _server)
	: baSocket(_server), m_server(_server)
{
}

bool ssSession::init()
{
	return true;
}

void ssSession::release()
{
}

void ssSession::issueRecv()
{
	baSocket::async_read_some(m_recvBuffer.toMutableBuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			this->onCompleteRecv(_ec, _len);
		});
}

void ssSession::issueSend()
{
	baSocket::async_write_some(m_sendBuffer.toConstbuffer(),
		[this](const bsErrorCode& _ec, std::size_t _len)
		{
			this->onCompleteSend(_ec, _len);
		});
}

void ssSession::issueConnect(const baEndpoint _ep)
{
	baSocket::async_connect(_ep,
		[this](const bsErrorCode& _ec)
		{
			this->onCompleteConnect(_ec);
		});
}
