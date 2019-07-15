#pragma once

#include <atomic>
#include <string>
#include <mutex>
#include <map>

#define WRITE(...)

enum LOG_LEVEL { DISABLE, INFO, WARN, ERR, TRACE, DEBUG };

class Log
{
private:
	// typedef vs using
	// https://unikys.tistory.com/381
	std::map<const char*, std::mutex>	m_Lock;
	std::atomic<int>	m_LogLevel;
	const char*			m_FileName;
	const char*			m_Type;

public:
	Log() = delete;
	Log(LOG_LEVEL logLevel, const char* fileInfo, const char* type);

	void ChangeLogLevel(LOG_LEVEL logLevel);

	LOG_LEVEL GetCurrentLogLevel();

	void Write(std::string msg, LOG_LEVEL logLevel);
};
