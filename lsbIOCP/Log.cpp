#include "Log.h"

#define MAP_ITER		first
#define MUTEX_PTR		second
#define INSERT_SUCCESS	second

Log::Log(LOG_LEVEL logLevel, std::string fileName, std::string type) : m_FileName(fileName), m_Type(type)
{
	ChangeLogLevel(logLevel);

	// map insert tip
	// https://yonmy.com/archives/9
	// performance of string key map
	// http://veblush.blogspot.com/2012/10/map-vs-unorderedmap-for-string-key.html
	auto res = m_Lock.insert({ fileName, nullptr });
	if (res.INSERT_SUCCESS)
	{ 
		res.MAP_ITER->MUTEX_PTR = new std::mutex(); 
	}
}

Log::~Log()
{
	for (auto& [_, mutex_ptr] : m_Lock)
	{
		delete mutex_ptr;
	}
}

void Log::ChangeLogLevel(LOG_LEVEL logLevel)
{
	m_LogLevel.store((int)logLevel);
}

LOG_LEVEL Log::GetCurrentLogLevel()
{
	return (LOG_LEVEL)m_LogLevel.load();
}

/**
 * 1. ���� �̸����� ���� �ɾ��ִ� ��� (��¥���� ���ϸ��� �޶����Ƿ� �ð��� ����)
 * 2. concurrent_queue�� ��� �α׸� �����ϰ�,
 *	  �ش� ť���� �α׸޽����� ������ ���ִ� ��׶��� �����带 �̿��ϴ� ���
 *		- �̰͵�.. ���Ϻ��� ť�� ������� ���� ����..
 *		- ������ ��׶��� �۾����� �α׸� �󸶳� ���� �����ϰ� �󸶳� ���� �ؾ� �ϴ��� ���
 * �߰���.. ���� I/O ���ķ� ���� �Ŵ� ���� ���� �ൿ�ΰ�..
 */
void Log::Write(std::string msg) { Log::Write(msg, LOG_LEVEL::INFO); }
void Log::Write(std::string msg, LOG_LEVEL logLevel)
{
	if (m_LogLevel.load() < (int)logLevel) return;

	std::string time = utils::GetTime();
	std::string date = utils::GetDate();

	std::stringstream ss;
	ss << "[" << date << "-" << time << "] " << m_Type << " -> " << msg;
	std::string logMsg = ss.str();

	// TODO: split files if size exceeds threshold (not by date)
	// TODO: make dir if it dosen't exist
	ss.str(std::string());
	ss << "./Log/" << m_FileName << "_" << date << ".txt";
	std::string filePath = ss.str();

	Log::FlushToFile(m_FileName, filePath, logMsg);
}

void Log::FlushToFile(std::string& fileName, std::string& filePath, std::string& logMsg)
{
	// Manage mutex variables to map by file name (except for date in file name)
	std::mutex* ioMutex;
	auto res = m_Lock.insert({ fileName, nullptr });
	if (res.INSERT_SUCCESS)
	{
		res.MAP_ITER->MUTEX_PTR = new std::mutex();
		ioMutex = res.MAP_ITER->MUTEX_PTR;
	}
	else
	{ 
		ioMutex = res.MAP_ITER->MUTEX_PTR; 
	}

	// Is iofstream thread safe ?
	// https://stackoverflow.com/questions/20211935/is-ofstream-thread-safe
	std::lock_guard<std::mutex> lock(*ioMutex);

	// Fail if there dosen't exist dir in path
	std::ofstream out(filePath, std::ios_base::out | std::ios_base::app);
	if (out.is_open()) 
	{ 
		out << logMsg; 
	}
	else 
	{ 
		std::cout << logMsg; 
	}
}