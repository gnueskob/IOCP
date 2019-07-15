#include <Ws2tcpip.h>
#include <thread>
#include <string>
#include <sstream>

#include "Acceptor.h"
#include "AIOException.h"

#pragma comment(lib, "ws2_32.lib")

Acceptor::Acceptor(const char* ip, const u_short port) : m_ip(ip), m_port(port)
{
	if (m_ws2_32_lib == false)
	{
		WSADATA wsaData;
		WORD wVer = MAKEWORD(2, 2);
		ThrowLastErrorIf(WSAStartup(wVer, &wsaData) != NO_ERROR, "[WSAStartup()] Error occured");
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			WSACleanup();
			ThrowLastErrorIf(true, "[WSAStartup()] WSA version not matched");
		}
	}
	m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ThrowLastErrorIf(m_listenSocket == INVALID_SOCKET, "[socket()] socket dosen't created");

	SOCKADDR_IN sin;
	sin.sin_port = htons(port);
	inet_pton(sin.sin_family = AF_INET, ip, &sin.sin_addr);

	int res;
	res = bind(m_listenSocket, (LPSOCKADDR)& sin, sizeof(sin));
	ThrowLastErrorIf(res == SOCKET_ERROR, "[bind()] Fail bind");

	res = listen(m_listenSocket, 128);
	ThrowLastErrorIf(res == SOCKET_ERROR, "[listen()] Fail listen");
	
	std::stringstream ss;
	ss << ip << '-' << port;
	m_Log = new Log(LOG_LEVEL::DEBUG, ss.str().c_str());

	m_Log->Write(LOG_LEVEL::INFO, "[%s, %d] accept started\n", ip, port);
}

DWORD Acceptor::Accept()
{
	SOCKET clientSocket = INVALID_SOCKET;
	SOCKADDR_IN addr;
	int len = sizeof(addr);

	while (this->IsStart())
	{
		clientSocket = accept(m_listenSocket, (sockaddr*)& addr, &len);

		if (clientSocket == INVALID_SOCKET)
		{
			m_Log->Write(LOG_LEVEL::INFO, "Accept Error %u", ::GetLastError());
			continue;
		}

		m_Log->Write(LOG_LEVEL::INFO, "Accepted %u.%u.%u.%u",
			addr.sin_addr.S_un.S_un_b.s_b1,
			addr.sin_addr.S_un.S_un_b.s_b2,
			addr.sin_addr.S_un.S_un_b.s_b3,
			addr.sin_addr.S_un.S_un_b.s_b4);

		// Server socket register
	}

	return 1;
}

DWORD Acceptor::Run()
{
	return Acceptor::Accept();
}