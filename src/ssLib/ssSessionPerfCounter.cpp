﻿#include <stdafx.hpp>
#include <ssLib.hpp>



// TODO : c++ 스타일로 정리하자
const std::string currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

void printPerf(const std::chrono::milliseconds _duration,
	const std::string& _totalName, const std::string& _tickName,
	const int _nTotalCount, const int _nTickCount)
{
	using namespace std;

	cout << currentDateTime() << " : [" << cout.width(4) << _duration.count() << "]ms / "
		<< _totalName << "[" << cout.width(6) << _nTotalCount << "] / "
		<< _tickName << "[" << cout.width(6) << _nTickCount << "]" << std::endl;
}



void ssSessionPerfCounter::setNextTick()
{
	m_nextTick = m_nextTick + std::chrono::seconds(1);
}

void ssSessionPerfCounter::onTick()
{
	using namespace std::chrono;

	const time_point now = system_clock::now();
	const auto msDuration = duration_cast<milliseconds>(now + seconds(1) - m_nextTick);

	if (0 < m_nTickRecv) printPerf(msDuration, "totalRecv", "tickRecv", m_nTotalRecv, m_nTickRecv);
	if (0 < m_nTickSend) printPerf(msDuration, "totalSend", "tickSend", m_nTotalSend, m_nTickSend);
	if (0 < m_nTickConn) printPerf(msDuration, "totalConn", "tickConn", m_nTotalConn, m_nTickConn);
	if (0 < m_nTickAcpt) printPerf(msDuration, "totalAcpt", "tickAcpt", m_nTotalAcpt, m_nTickAcpt);

	m_nTickRecv = 0;
	m_nTickSend = 0;
	m_nTickConn = 0;
	m_nTickAcpt = 0;
}