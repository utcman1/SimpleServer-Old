// TODO : circular buffer로 변환이 필요하다.



class ssBuffer
{
private:
	typedef std::size_t size_t;

private:
	enum { EC_Capacity = 4096 - sizeof(size_t) };

	size_t	m_size = 0;
	char	m_buffer[EC_Capacity];

private:
	char* ssBuffer::nextPtr();

public:
	// Capacity
	size_t capacity() const { return EC_Capacity; }
	size_t size() const { return m_size; }
	bool empty() const { return 0 == m_size; }

	// Modifiers
	void clear();
	void completePop(const size_t _len);
	void completePush(const size_t _len);
	void push(const char* _buffer, const size_t _len);
	void push(ssBuffer& _src);

	// Cast Operator
	baConstBuffer toConstbuffer() const;
	baMutableBuffer toMutableBuffer();
};
