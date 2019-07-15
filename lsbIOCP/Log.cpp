#include "Log.h"

Log::Log(LOG_LEVEL logLevel, std::string fileInfo, std::string type) : m_FileName(fileInfo), m_Type(type)
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

void Log::Write(std::string msg) { Log::Write(msg, LOG_LEVEL::INFO); }
void Log::Write(std::string msg, LOG_LEVEL logLevel)
{
	if (m_LogLevel.load() < (int)logLevel) return;

	char szpath[256] = { 0, };
	char szbuff[512] = { 0, };

	std::string time = utils::GetTime();
	std::string date = utils::GetDate();

	std::stringstream ss;
	ss << "[" << date << "-" << time << "] -> " << msg;

	std::string logMsg = ss.str();

	ss.str(std::string());
	ss << "./Log/" << m_Type << "/[" << date.c_str() << "]_" << m_FileName << ".txt";
	std::string filePath = ss.str();

	// Is iofstream thread safe ?
	// https://stackoverflow.com/questions/20211935/is-ofstream-thread-safe

	#define MAP_ITER		first
	#define MUTEX_PTR		second
	#define INSERT_SUCCESS	second

	// map insert tip
	// https://yonmy.com/archives/9
	std::mutex* fileLock;
	auto res = m_Lock.insert({ filePath, nullptr });
	if (res.INSERT_SUCCESS)
	{
		res.MAP_ITER->MUTEX_PTR = new std::mutex();
		fileLock = res.MAP_ITER->MUTEX_PTR;
	}
	else { fileLock = res.MAP_ITER->MUTEX_PTR; }

	{
		std::lock_guard<std::mutex> lock(*fileLock);

		// 경로 상에 폴더가 없으면 실패
		using ios = std::ios_base;
		std::ofstream out(filePath, ios::out | ios::app);
		if (out.is_open()) { out << logMsg; }
		else { std::cout << logMsg; }
	}
}