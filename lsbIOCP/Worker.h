#pragma once

#include <winsock2.h>
#include <MSWSock.h>

#include "Log.h"
#include "Session.h"
#include "IServer.h"
#include "SessionManager.h"
#include "Utils.h"
#include "Thread.h"

// For avoid cross reference of header "AsyncIONetwork.h"
// #include is declared in .cpp file
class AsyncIONetwork;

class Worker : public Thread
{
public:
	Worker() = delete;
	Worker(
		IServerReceiver* const pReceiver, 
		const HANDLE iocpHandle, 
		SessionManager* const pSessionManager, 
		AsyncIONetwork* const pServer, 
		Log* const pLog);
	void Run() override;

private:
	void HandleCompletion();
	void DispatchError(DWORD error, LPOVERLAPPED lpOverlapped, INT id);
	void DispatchCompleteion(DWORD transferredBytesNumber, LPOVERLAPPED lpOverlapped, INT id);

private:
	IServerReceiver* const		m_pReceiver;
	SessionManager* const		m_pSessionManager;
	AsyncIONetwork* const	 	m_pServer;
	HANDLE				m_IOCPHandle;
	Log*				m_Log;
};