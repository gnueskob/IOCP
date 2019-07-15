#include <windows.h>

#include "Log.h"

Log::Log()
{
	m_LogMsgQueue = new ccqStr();
	ChangeLogLevel(LOG_LEVEL::INFO);
}

Log::Log(LOG_LEVEL logLevel)
{
	m_LogMsgQueue = new ccqStr();
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

void Log::Write(const char* format, ...)
{
	char szpath[256] = { 0, };
	char szbuff[512] = { 0, };
	char szdate[256] = { 0, };
	char sztime[256] = { 0, };

	// 시간 처리
	// https://araikuma.tistory.com/597
	// https://m.blog.naver.com/PostView.nhn?blogId=igazoa2&logNo=220271308803&proxyReferer=https%3A%2F%2Fwww.google.com%2F
	time_t now;
	time(&now);
	tm date;
	localtime_s(&date, &now);
	strftime(szdate, 256, "%Y_%m_%d", &date);
	_strtime_s(sztime, 256);

	_snprintf_s(szbuff, 512, "%s(%s)->", szdate, sztime);

	// 가변인자
	// https://dojang.io/mod/page/view.php?id=577
	// https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/d3xd30zz(v=vs.90)
	va_list marker;
	va_start(marker, format);
	_vsnprintf_s(szbuff + strlen(szbuff), 512 - strlen(szbuff), _TRUNCATE, format, marker);
	va_end(marker);

	sprintf_s(szpath, "./acceptor/Accept_[%s-%u][%s].txt", m_ip, m_port, szdate);

	fwrite(szpath, strlen(szpath), 1, stdout);

	FILE* fp = nullptr;
	auto err = fopen_s(&fp, szpath, "at");

	if (fp != 0)
	{
		fwrite(szbuff, strlen(szbuff), 1, fp);
		fclose(fp);
		fp = NULL;
	}
}