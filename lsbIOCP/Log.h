#pragma once

#include <concurrent_queue.h>
#include <atomic>
#include <string>

enum LOG_LEVEL { DISABLE, INFO, WARN, ERROR, TRACE, DEBUG };

class Log
{
private:
	// typedef vs using
	// https://unikys.tistory.com/381
	using ccqStr = Concurrency::concurrent_queue<std::string>;
	ccqStr* m_LogMsgQueue;
	std::atomic<int> m_LogLevel;

public:
	Log();
	Log(LOG_LEVEL logLevel);

	void ChangeLogLevel(LOG_LEVEL logLevel);

	LOG_LEVEL GetCurrentLogLevel();

	void Write(const char* format, ...);

	bool GetLog(std::string* msg);
};
