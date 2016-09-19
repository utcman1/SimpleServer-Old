#include <stdafx.hpp>
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
	const std::size_t _nTotalCount, const std::size_t _nTickCount)
{
	std::printf("%s : [%04lld]ms / %s[%06zd] / %s[%06zd]\n",
		currentDateTime().c_str(), _duration.count(),
		_totalName.c_str(), _nTotalCount,
		_tickName.c_str(), _nTickCount);
}



void ssSessionPerfCounter::reserveNextTick()
{
	baSystemTimer::expires_at(m_lastTick + milliseconds(1000));

	baSystemTimer::async_wait(
		[this](const bsErrorCode& _ec)
		{
			const time_point now = system_clock::now();

			if (_ec)
			{
				ssERROR << _ec.message();
			}
			else
			{
				this->onTick(now);
			}

			this->m_lastTick += milliseconds(1000);
			this->reserveNextTick();
		});
}

bool ssSessionPerfCounter::init()
{
	m_lastTick = system_clock::now();
	ssSessionPerfCounter::reserveNextTick();

	m_nTotalAcpt = 0;
	m_nTotalConn = 0;
	m_nTotalRecv = 0;
	m_nTotalSend = 0;

	m_nTickAcpt = 0;
	m_nTickConn = 0;
	m_nTickRecv = 0;
	m_nTickSend = 0;

	return true;
}

void ssSessionPerfCounter::onTick(const time_point& _now)
{
	using namespace std::chrono;

	const auto msDuration = duration_cast<milliseconds>(_now - m_lastTick);

	if (0 < m_nTickAcpt) printPerf(msDuration, "totalAcpt", "tickAcpt", m_nTotalAcpt, m_nTickAcpt);
	if (0 < m_nTickConn) printPerf(msDuration, "totalConn", "tickConn", m_nTotalConn, m_nTickConn);
	if (0 < m_nTickRecv) printPerf(msDuration, "totalRecv", "tickRecv", m_nTotalRecv, m_nTickRecv);
	if (0 < m_nTickSend) printPerf(msDuration, "totalSend", "tickSend", m_nTotalSend, m_nTickSend);

	m_nTickAcpt = 0;
	m_nTickConn = 0;
	m_nTickRecv = 0;
	m_nTickSend = 0;
}
