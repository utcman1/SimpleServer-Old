class ssINonCopyable
{
public:
	ssINonCopyable() = default;
	~ssINonCopyable() = default;

	// copy constructor
	ssINonCopyable(const ssINonCopyable&) = delete;
	ssINonCopyable& operator=(const ssINonCopyable&) = delete;

	// move constructor
	ssINonCopyable(const ssINonCopyable&&) = delete;
	ssINonCopyable& operator=(const ssINonCopyable&&) = delete;
};
