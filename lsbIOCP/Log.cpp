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

	std::string time = utils::GetTime();
	std::string date = utils::GetDate();

	std::stringstream ss;
	ss << "[" << date << "-" << time << "] -> " << msg;
	std::string logMsg = ss.str();

	// TODO: make dir if it dosen't exist
	ss.str(std::string());
	ss << "./Log/" << m_Type << "/[" << date << "]_" << m_FileName << ".txt";
	std::string filePath = ss.str();

	// Is iofstream thread safe ?
	// https://stackoverflow.com/questions/20211935/is-ofstream-thread-safe
	// 1. 파일 타입별로 락을 걸어주는 방법
	//		- Acceptor / AsyncIO 별로 락이걸림
	// 2. concurrent_queue로 모든 로그를 저장하고,
	//	  해당 큐에서 로그메시지를 꺼내서 써주는 백그라운드 스레드를 이용하는 방법
	//		- 이것도.. 타입별로 큐를 만들어줄 수는 있음..
	//		- 하지만 백그라운드 작업에서 로그를 얼마나 자주 쓰게하고 얼마나 쉬게 해야 하는지 고민
	// 추가로.. 파일 I/O 전후로 락을 거는 것이 옳은 행동인가..
	{
		std::mutex* ioMutex = Log::GetMutex(m_Type);
		std::lock_guard<std::mutex> lock(*ioMutex);

		// 경로 상에 폴더가 없으면 실패
		using ios = std::ios_base;
		std::ofstream out(filePath, ios::out | ios::app);
		if (out.is_open()) { out << logMsg; }
		else { std::cout << logMsg; }
	}
}

#define MAP_ITER		first
#define MUTEX_PTR		second
#define INSERT_SUCCESS	second
std::mutex* Log::GetMutex(std::string fileType)
{
	// map insert tip
	// https://yonmy.com/archives/9
	std::mutex* ioMutex;
	auto res = m_Lock.insert({ fileType, nullptr });
	if (res.INSERT_SUCCESS)
	{
		res.MAP_ITER->MUTEX_PTR = new std::mutex();
		ioMutex = res.MAP_ITER->MUTEX_PTR;
	}
	else { ioMutex = res.MAP_ITER->MUTEX_PTR; }

	return ioMutex;
}