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

class AsyncIOServer : public IServerController
{
public:
	AsyncIOServer() = delete;
	AsyncIOServer(
		IServerReceiver* const pReceiver,
		const INT ioMaxSize,
		const INT threadNumber,
		const INT sessionNumber,
		const INT sessionMaxNum,
		const std::string name,
		const char* const ip,
		const u_short port);
	~AsyncIOServer();
	void Start();
	void Stop();
	void Join();

	SESSION* LinkSocketToSession(SOCKET clientSocket);
	DWORD UnlinkSocketToSession(INT sessionId, DWORD error);
	DWORD RegisterClient(SOCKET clientSocket);

	// IServerController
	DWORD SendPacket(SESSIONDESC& sessionDesc, size_t length, char* data) override;
	DWORD ConnectSocket(INT requestId, const char* ip, u_short port) override;
	DWORD DisconnectSocket(SESSIONDESC& sessionDesc) override;

private:
	IServerReceiver*		m_pReceiver;
	Acceptor*		m_pAcceptor;

	HANDLE			m_IOCPHandle;

	static size_t	IO_MIN_SIZE;
	size_t			m_IOMaxSize;

	size_t			m_ThreadNum;
	workers			m_Workers;

	std::string		m_ServerName;
	Log*			m_Log;

	SessionManager*		m_pSessionManager;
};