#pragma once

#include <atomic>
#include <string>
#include <mutex>
#include <sstream>
#include <fstream>
#include <iostream>

#include "ILog.h"
#include "Utils.h"

#pragma warning( push )
#pragma warning( disable : 4244 )
//http://cppconlib.codeplex.com/
//http://mariusbancila.ro/blog/2013/08/25/cppconlib-a-cpp-library-for-working-with-the-windows-console/
#include "conmanip.h"
using namespace conmanip;
#pragma warning( pop )

class Log : public ILog
{
public:
	void Init(LOG_LEVEL logLevel, std::string& fileName);

	void ChangeLogLevel(LOG_LEVEL logLevel);

	LOG_LEVEL GetCurrentLogLevel();

	virtual void Write(const LOG_LEVEL nType, const char* pFormat, ...) override;

protected:
	virtual void Error(const char* pText) override;
	virtual void Warn(const char* pText) override;
	virtual void Debug(const char* pText) override;
	virtual void Trace(const char* pText) override;
	virtual void Info(const char* pText) override;

private:
	void Flush(const char* logMsg, LOG_LEVEL logLevel);

private:
	// typedef vs using
	// https://unikys.tistory.com/381

	std::mutex			m_Lock;
	std::atomic<int>	m_LogLevel;
	std::string			m_FileName;
};