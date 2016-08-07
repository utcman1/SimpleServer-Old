#include <stdafx.hpp>
#include <ssLib/ssLib.hpp>



char* ssCBuffer::nextPtr()
{
	return (m_buffer + m_size);
}

void ssCBuffer::pushData(const char* _src, const std::size_t _len)
{
	assert(size() + _len <= capacity());
	memcpy(nextPtr(), _src, _len);
	m_size += _len;
}



bool ssCBuffer::isCompletePacket() const
{
	// TODO : echo 서버를 위한 임시 구현
	// 정식으로 구현하기 위해서는 Packet에 대한 정보가 필요하다.
	return (0 < m_size);
}

void ssCBuffer::clear()
{
	m_size = 0;
}

void ssCBuffer::pop(const std::size_t _len)
{
	assert(size() >= _len);
	m_size -= _len;
	memmove(m_buffer, m_buffer + _len, m_size);
}

void ssCBuffer::push(const std::size_t _len)
{
	assert(size() + _len <= capacity());
	m_size += _len;
}

void ssCBuffer::moveTo(ssCBuffer& _dst)
{
	ssCBuffer& src = *this;

	const std::size_t moveLen = std::min(src.size(), _dst.capacity() - _dst.size());

	if (0 < moveLen)
	{
		_dst.pushData(src.m_buffer, moveLen);
		src.pop(moveLen);
	}
}

BAConstBuffer ssCBuffer::toConstbuffer() const
{
	return BAConstBuffer(m_buffer, size());
}

BAMutableBuffer ssCBuffer::toMutableBuffer()
{
	return BAMutableBuffer(nextPtr(), capacity() - size());
}
