// TODO : circular buffer 도입하자.
// TODO : buffer block을 단일 block이 아닌
//			작은 block(64 byte) : 높은 빈도로 사용됨. class에 직접 포함.
//			큰 block(64K byte) : 낮은 빈도로 사용됨. 외부의 메모리 풀을 사용.
//			2단계로 구성해서 작은 block의 경우 메모리 사용 효율을 높일 수 있도록 구성하자.



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
