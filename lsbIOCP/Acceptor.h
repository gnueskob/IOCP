#pragma once

#include <windows.h>

#include "Log.h"
#include "Thread.h"

class Acceptor : public Thread
{
public:
	Acceptor() = delete;
	Acceptor(const char* ip, const u_short port);
	~Acceptor() = default;
	DWORD Run() override;

private:
	DWORD Accept();

private:
	SOCKET			m_listenSocket;
	const char*		m_ip;
	const u_short	m_port;
	bool			m_ws2_32_lib = false;
	Log*			m_Log;
};