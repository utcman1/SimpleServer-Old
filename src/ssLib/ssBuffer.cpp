#include <stdafx.hpp>
#include <ssLib.hpp>



char* ssBuffer::nextPtr()
{
	return (m_buffer + m_size);
}



void ssBuffer::clear()
{
	m_size = 0;
}

void ssBuffer::completePop(const size_t _len)
{
	assert(size() >= _len);
	m_size -= _len;
	memmove(m_buffer, m_buffer + _len, m_size);
}

void ssBuffer::completePush(const size_t _len)
{
	assert(size() + _len <= capacity());
	m_size += _len;
}

void ssBuffer::push(const char* _src, const size_t _len)
{
	assert(size() + _len <= capacity());
	memcpy(nextPtr(), _src, _len);
	completePush(_len);
}

void ssBuffer::push(ssBuffer& _src)
{
	ssBuffer& dst = *this;

	const size_t moveLen = std::min(_src.size(), dst.capacity() - dst.size());
	if (0 < moveLen)
	{
		dst.push(_src.m_buffer, moveLen);
		_src.completePop(moveLen);
	}
}

baConstBuffer ssBuffer::toConstbuffer() const
{
	return baConstBuffer(m_buffer, size());
}

baMutableBuffer ssBuffer::toMutableBuffer()
{
	return baMutableBuffer(nextPtr(), capacity() - size());
}
