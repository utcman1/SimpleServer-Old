class ssINonCopyable
{
public:
	// constructor
	ssINonCopyable() = default;
	~ssINonCopyable() = default;

	// copy constructor, assignment operator
	ssINonCopyable(const ssINonCopyable&) = delete;
	ssINonCopyable& operator=(const ssINonCopyable&) = delete;

	// move constructor
	ssINonCopyable(const ssINonCopyable&&) = delete;
	ssINonCopyable& operator=(const ssINonCopyable&&) = delete;
};
