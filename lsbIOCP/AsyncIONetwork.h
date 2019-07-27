#pragma once

#include <Ws2tcpip.h>

#include <vector>
#include <functional>

#include "Log.h"
#include "Utils.h"
#include "Worker.h"
#include "SessionManager.h"
#include "Acceptor.h"
#include "AsyncIOException.h"

using workers = std::vector<std::shared_ptr<Worker>>;

class AsyncIONetwork : public IServerController
{
public:
	AsyncIONetwork() = delete;
	AsyncIONetwork(IServerReceiver* const pReceiver, ServerConfig config);
	~AsyncIONetwork();
	void Start();
	void Stop();
	void Join();

	SESSION* LinkSocketToSession(SOCKET clientSocket);
	DWORD UnlinkSocketToSession(INT sessionId, DWORD error);
	DWORD RegisterClient(SOCKET clientSocket);

	// IServerController
	DWORD SendPacket(const INT sessionId, short length, char* data, short headerLength, char* header) override;
	DWORD ConnectSocket(INT requestId, const char* ip, u_short port) override;
	DWORD DisconnectSocket(const INT sessionId) override;

private:
	// Handler
	IServerReceiver*	m_pReceiver;
	SessionManager*		m_pSessionManager;
	Acceptor*			m_pAcceptor;
	HANDLE				m_IOCPHandle;

	// AsyncIONetwork config
	INT				m_ThreadNum;
	workers			m_Workers;
	std::string		m_ServerName;

	// Logger
	Log*			m_Log;
};