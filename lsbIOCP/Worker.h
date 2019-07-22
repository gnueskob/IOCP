#pragma once

#include <winsock2.h>
#include <MSWSock.h>

#include "Session.h"
#include "IServer.h"
#include "SessionManager.h"
#include "Log.h"
#include "Utils.h"
#include "Thread.h"

// For avoid cross reference of header "AsyncIOServer.h"
// #include is declared in .cpp file
class AsyncIOServer;

class Worker : public Thread
{
public:
	Worker() = delete;
	Worker(IServerReceiver* pReceiver, HANDLE iocpHandle, SessionManager* sessionManager, AsyncIOServer* pServer);
	void Run() override;

private:
	void HandleCompletion();
	void DispatchError(DWORD error, LPOVERLAPPED lpOverlapped, INT id);
	void DispatchCompleteion(DWORD transferredBytesNumber, LPOVERLAPPED lpOverlapped, INT id);

private:
	IServerReceiver*	m_pReceiver;
	SessionManager*		m_pSessionManager;
	AsyncIOServer*		m_pServer;
	HANDLE				m_IOCPHandle;
	Log*				m_Log;
};