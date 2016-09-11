// TODO : circular buffer로 변환이 필요하다.



class ssBuffer
{
	typedef std::size_t size_t;

private:
	enum { EC_Capacity = 4096 - sizeof(size_t) };

	size_t	m_size = 0;
	char	m_buffer[EC_Capacity];

private:
	char* ssBuffer::nextPtr();
	void pushData(const char* _buffer, const size_t _len);

public:
	// Capacity
	size_t capacity() const { return EC_Capacity; }
	size_t size() const { return m_size; }
	bool empty() const { return 0 == m_size; }
	bool isCompletePacket() const;

	// Modifiers
	void clear();
	void pop(const size_t _len);
	void push(const size_t _len);
	void moveTo(ssBuffer& _dst);

	// Cast Operator
	baConstBuffer toConstbuffer() const;
	baMutableBuffer toMutableBuffer();
};
