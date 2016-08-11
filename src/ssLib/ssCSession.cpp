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

void ssCSession::onCompleteSend(const BErrorCode& _ec, const std::size_t _len)
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

void ssCSession::onCompleteConnect(const BErrorCode& _ec)
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



ssCSession::ssCSession(ssCService& _server)
	: BASocket(_server), m_server(_server)
{
}

bool ssCSession::init()
{
	return true;
}

void ssCSession::release()
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

void ssCSession::issueConnect(const BAEndpoint _ep)
{
	BASocket::async_connect(_ep,
		[this](const BErrorCode& _ec)
		{
			this->onCompleteConnect(_ec);
		});
}
