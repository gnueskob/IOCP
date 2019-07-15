#include <sstream>

#include "Log.h"
#include "Utils.h"

Log::Log(LOG_LEVEL logLevel, const char* fileInfo, const char* type) : m_FileName(fileInfo), m_Type(type)
{
	ChangeLogLevel(logLevel);
}

void Log::ChangeLogLevel(LOG_LEVEL logLevel)
{
	m_LogLevel.store((int)logLevel);
}

LOG_LEVEL Log::GetCurrentLogLevel()
{
	return (LOG_LEVEL)m_LogLevel.load();
}

void Log::Write(std::string msg, LOG_LEVEL logLevel = LOG_LEVEL::INFO)
{
	if (m_LogLevel < (int)logLevel) return;

	char szpath[256] = { 0, };
	char szbuff[512] = { 0, };

	std::string time = GetTime();
	std::string date = GetDate();

	std::stringstream ss;

	ss << '[' << date << '-' << time << ']';
	std::string currentDateTime = ss.str();

	// _snprintf_s(szbuff, 512, "%s(%s)->", szdate, sztime);

	// sprintf_s(szpath, "./Log/%s/%s_[%s].txt", m_Type, m_FileName, date.c_str());

	ss.str(std::string());
	ss << "./Log/" << m_Type << "/" << m_FileName << "_[" << date.c_str() << "].txt";
	std::string filePath = ss.str();

	FILE* fp = nullptr;
	auto err = fopen_s(&fp, szpath, "at");

	{
		std::lock_guard<std::mutex>	lock(m_Lock);
		if (fp != 0)
		{
			fwrite(szbuff, strlen(szbuff), 1, fp);
			fclose(fp);
			fp = NULL;
		}
		else
		{
			fwrite(szpath, strlen(szpath), 1, stdout);
		}
	}
}