#pragma once

#include <windows.h>
#include <mutex>

#include "Struct.h"
#include "IServer.h"

class Session
{
public:
	Session() = default;
	Session(IServerController* pController);

	void SetSocket(SOCKET socket);
	const SOCKET GetSocket() const;
	// TODO: add/sub refCount, set controller

public:
	IServerController* m_pController;

private:
	std::mutex			m_SendLock;
	SOCKET				m_SocketId = 0;
	std::atomic_int		m_RefCount = 0;
	std::atomic_bool	m_Closed = true;
	OVERLAPPED_EX		m_OverlappedSend;
	OVERLAPPED_EX		m_OverlappedRecv;
	OVERLAPPED_EX		m_OverlappedConn;
};
