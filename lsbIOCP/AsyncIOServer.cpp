#include "AsyncIOServer.h"

size_t AsyncIOServer::IO_MIN_SIZE = 1024;

AsyncIOServer::AsyncIOServer(
	IServerReceiver* pReceiver,
	DWORD ioMaxSize,
	DWORD threadNumber,
	DWORD sessionNumber,
	std::string name)
	: m_pReceiver(pReceiver)
	, m_IOMaxSize(ioMaxSize)
	, m_ThreadNum(threadNumber)
	, m_ServerName(name)
	, m_IOCPHandle(INVALID_HANDLE_VALUE)
	, m_Log(Log::GetInstance())
{
	Log::GetInstance()->Init(LOG_LEVEL::DEBUG, name);

	if (name == "") 
	{
		m_ServerName = utils::Format("AsyncIOServer_%d", ::GetCurrentThreadId()); 
	}

	ThrowErrorIf(pReceiver == nullptr, WSAEINVAL, "Receiver nullptr");
	ThrowErrorIf(threadNumber < 1, WSAEINVAL, "Thread number must over than 0");
	ThrowErrorIf(IO_MIN_SIZE > ioMaxSize, WSAEMSGSIZE, "ioMaxSize is too small than IO_MIN_SIZE");
	ThrowErrorIf(SessionManager::SESSION_MAX_NUMBER < sessionNumber, WSAENOBUFS, "Session number exceeds max value");

	m_IOCPHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, static_cast<ULONG_PTR>(0), threadNumber);

	ThrowLastErrorIf(m_IOCPHandle == INVALID_HANDLE_VALUE, "Fail create IOCP");
	
	m_pSessinManager = new SessionManager(sessionNumber, ioMaxSize, this);

	for (DWORD i = 0; i < threadNumber; i++)
	{
		m_Workers.push_back(std::make_shared<Worker>(pReceiver, m_IOCPHandle, m_pSessinManager));
	}

	m_Log->Write("Server Initialized succesfully");
};

AsyncIOServer::~AsyncIOServer()
{
	if (INVALID_HANDLE_VALUE != m_IOCPHandle)
	{
		CloseHandle(m_IOCPHandle);
	}
}

void AsyncIOServer::Start()
{
	for (auto& worker : m_Workers)
	{
		worker->Start();
	}
}

void AsyncIOServer::Stop()
{
	for (auto& worker : m_Workers)
	{
		worker->Stop();
	}
}

void AsyncIOServer::registerSocket(SOCKET clientSocket)
{
	ThrowErrorIf(INVALID_SOCKET == clientSocket, WSAENOTSOCK, "Client socket is invalid");
	
	return;
}

void AsyncIOServer::postRecv(SESSION* session)
{
	session->enterIO();
}