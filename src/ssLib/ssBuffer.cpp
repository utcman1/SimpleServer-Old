#include <stdafx.hpp>
#include <ssLib.hpp>



char* ssBuffer::nextPtr()
{
	return (m_buffer + m_size);
}

void ssBuffer::pushData(const char* _src, const std::size_t _len)
{
	assert(size() + _len <= capacity());
	memcpy(nextPtr(), _src, _len);
	m_size += _len;
}



bool ssBuffer::isCompletePacket() const
{
	// TODO : echo 서버를 위한 임시 구현
	// 정식으로 구현하기 위해서는 Packet에 대한 정보가 필요하다.
	// Buffer가 아닌 외부에 위치하도록 리팩토링이 맞을수도 있을거 같다.
	return (0 < m_size);
}

void ssBuffer::clear()
{
	m_size = 0;
}

void ssBuffer::pop(const std::size_t _len)
{
	assert(size() >= _len);
	m_size -= _len;
	memmove(m_buffer, m_buffer + _len, m_size);
}

void ssBuffer::push(const std::size_t _len)
{
	assert(size() + _len <= capacity());
	m_size += _len;
}

void ssBuffer::moveTo(ssBuffer& _dst)
{
	ssBuffer& src = *this;

	const std::size_t moveLen = std::min(src.size(), _dst.capacity() - _dst.size());

	if (0 < moveLen)
	{
		_dst.pushData(src.m_buffer, moveLen);
		src.pop(moveLen);
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
