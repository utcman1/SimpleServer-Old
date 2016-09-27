#include <stdafx.hpp>
#include <ssLib.hpp>



std::string getLocalTime()
{
	std::time_t	now = std::time(nullptr);
	struct tm	tstruct;
	char		buf[64];
#ifdef _WIN32
	localtime_s(&tstruct, &now);
#else
	localtime_r(&now, &tstruct);
#endif
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}
