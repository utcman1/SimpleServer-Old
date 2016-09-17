﻿class ssSessionPerfCounter
{
private:
	typedef std::chrono::system_clock system_clock;
	typedef std::chrono::system_clock::time_point time_point;
	typedef std::size_t size_t;

private:
	time_point m_lastTick = time_point::max();

	size_t m_nTotalRecv = 0;
	size_t m_nTotalSend = 0;
	size_t m_nTotalConn = 0;
	size_t m_nTotalAcpt = 0;

	size_t m_nTickRecv = 0;
	size_t m_nTickSend = 0;
	size_t m_nTickConn = 0;
	size_t m_nTickAcpt = 0;

public:
	bool init();
	void release() {}

	// framework에서 일정 주기로 호출할 함수.
	// perfCounter의 tick 주기는 외부에서 결정한다.
	void onTick();

	void countRecv()	{ ++m_nTotalRecv; ++m_nTickRecv; }
	void countSend()	{ ++m_nTotalSend; ++m_nTickSend; }
	void countConnect()	{ ++m_nTotalConn; ++m_nTickConn; }
	void countAccept()	{ ++m_nTotalAcpt; ++m_nTickAcpt; }
};
