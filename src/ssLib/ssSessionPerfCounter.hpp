class ssSessionPerfCounter
{
private:
	typedef std::chrono::system_clock system_clock;
	typedef std::chrono::system_clock::time_point time_point;

private:
	time_point m_lastTick = time_point::max();

	int m_nTotalRecv = 0;
	int m_nTotalSend = 0;
	int m_nTotalConn = 0;
	int m_nTotalAcpt = 0;

	int m_nTickRecv = 0;
	int m_nTickSend = 0;
	int m_nTickConn = 0;
	int m_nTickAcpt = 0;

private:
	void setLastTick();

public:
	bool init();
	void release() {}

	// framework에서 일정 주기로 호출할 함수.
	// perfCounter의 tick 주기는 외부에서 결정한다.
	void onTick();

	void onRecv()		{ ++m_nTotalRecv; ++m_nTickRecv; }
	void onSend()		{ ++m_nTotalSend; ++m_nTickSend; }
	void onConnect()	{ ++m_nTotalConn; ++m_nTickConn; }
	void onAccept()		{ ++m_nTotalAcpt; ++m_nTickAcpt; }
};
