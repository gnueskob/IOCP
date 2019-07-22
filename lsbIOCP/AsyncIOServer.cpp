#include "AsyncIOServer.h"

AsyncIOServer::AsyncIOServer(
	IServerReceiver* const pReceiver,
	const INT ioMaxSize,
	const INT ioMinSize,
	const INT threadNumber,
	const INT sessionNumber,
	const INT sessionMaxNum,
	const std::string name,
	const char* const ip,
	const u_short port)
	: m_pReceiver(pReceiver)
	, m_ThreadNum(threadNumber)
	, m_ServerName(name)
	, m_IOCPHandle(INVALID_HANDLE_VALUE)
	, m_Log(Log::GetInstance())
{
	if (name == "") 
	{
		m_ServerName = "AsyncIOServer_" + utils::GetDate(); 
	}

	// Initialize Log file name, level
	Log::GetInstance()->Init(LOG_LEVEL::DEBUG, m_ServerName);

	// Config conditions
	ThrowErrorIf(ioMaxSize <= 0 || ioMinSize <= 0 || sessionMaxNum <= 0, 0UL, "configuration value is invalid");

	// Check conditions
	ThrowErrorIf(pReceiver == nullptr, WSAEINVAL, "Receiver nullptr");
	ThrowErrorIf(threadNumber < 1, WSAEINVAL, "Thread number must over than 0");
	ThrowErrorIf(ioMinSize > ioMaxSize, WSAEMSGSIZE, "ioMaxSize is too small than IO_MIN_SIZE");
	ThrowErrorIf(sessionMaxNum < sessionNumber, WSAENOBUFS, "Session number exceeds max value");

	// Create IOCP
	m_IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, static_cast<ULONG_PTR>(0), threadNumber);
	ThrowLastErrorIf(m_IOCPHandle == INVALID_HANDLE_VALUE, "Fail create IOCP");
	m_Log->Write("Create IOCP succesfully", LOG_LEVEL::DEBUG);
	
	// Initialize Session Manager (session pool, session id pool etc..)
	m_pSessionManager = new SessionManager(sessionNumber, sessionMaxNum, ioMaxSize, this);
	m_Log->Write("Create Session manager succesfully", LOG_LEVEL::DEBUG);

	// Initialize Worker threads
	for (INT i = 0; i < threadNumber; i++)
	{
		m_Workers.push_back(std::make_shared<Worker>(pReceiver, m_IOCPHandle, m_pSessionManager, this));
	}
	m_Log->Write(utils::Format("Create %d threads succesfully", threadNumber), LOG_LEVEL::DEBUG);

	m_Log->Write("Server Initialized succesfully");

	// Acceptor initialize
	// Apply acceptor to my server
	m_pAcceptor = new Acceptor(this, ip, port);
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
	m_pAcceptor->Start();
	for (auto& worker : m_Workers)
	{
		worker->Start();
	}
}

void AsyncIOServer::Stop()
{
	m_pAcceptor->Stop();
	for (auto& worker : m_Workers)
	{
		worker->Stop();
	}
}

void AsyncIOServer::Join()
{
	m_pAcceptor->Join();
	for (auto& worker : m_Workers)
	{
		worker->Join();
	}
}

// Apply socket id to available session
// Warning : not yet opend socket flag
SESSION* AsyncIOServer::LinkSocketToSession(SOCKET clientSocket)
{
	// Get available session id from 'session id pool' (concurrent queue)
	INT sessionId;
	if (m_pSessionManager->retrieveId(sessionId) == false) return nullptr;

	// Link this session socket with client socket
	auto pSession = m_pSessionManager->GetSessionPtr(sessionId);

	m_Log->Write(utils::Format("[session #%u] Socket added to session", pSession->GetSessionDescRef().id));

	// Add this socket to current IOCP handle using session id as completion key
	auto res = ::CreateIoCompletionPort(
		reinterpret_cast<HANDLE>(clientSocket),
		m_IOCPHandle,
		sessionId,
		0);

	if (res != m_IOCPHandle)
	{
		// If fail to add client socket to iocp handle,
		// return current session id to 'session id pool'
		m_pSessionManager->returnId(sessionId);
		return nullptr;
	}

	pSession->SetSocket(clientSocket);

	return pSession;
}

// Register already accepted client socket to server
// Then, notify to server the result and post receive
DWORD AsyncIOServer::RegisterClient(SOCKET clientSocket)
{
	// Apply socket id to available session
	auto pSession = LinkSocketToSession(clientSocket);
	if (pSession == nullptr) return WSAENOBUFS; // TODO: error

	// Socket is already accepted by accept() func.
	// So, set open flag
	pSession->Open();

	// Notify to server that client socket successfully connected with session descriptor
	m_pReceiver->NotifyClientConnected(pSession->GetSessionDescRef());

	// Post receive IOCP job
	auto error = m_pSessionManager->PostRecv(pSession);
	if (error != FALSE) {
		m_Log->Write(utils::Format("[Error %u] PostRecv failed", error), LOG_LEVEL::ERR);
		UnlinkSocketToSession(pSession->GetSessionId(), error);
	}

	return 0;
}

// Release current session id & close the socket if possible
DWORD AsyncIOServer::UnlinkSocketToSession(INT sessionId, DWORD error)
{
	auto pSession = m_pSessionManager->GetSessionPtr(sessionId);

	// Check this session is already closed, if not close socket
	if (pSession->Close())
	{
		closesocket(pSession->GetSocket());
		m_Log->Write(utils::Format("Socket closed %d", pSession->GetSocket()));
		m_pReceiver->NotifyClientDisconnected(pSession->GetSessionId());
	}

	// Initialize session socket
	pSession->SetSocket(INVALID_SOCKET);

	// Return session id to session id pool
	m_pSessionManager->returnId(sessionId);

	if (error == FALSE)
		m_Log->Write(utils::Format("[session #%u] Release Sokcet", sessionId));
	else
		m_Log->Write(utils::Format("[session #%u] Release Sokcet by Error #%d", sessionId, error), LOG_LEVEL::ERR);

	return 0;
}