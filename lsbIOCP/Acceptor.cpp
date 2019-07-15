#include <Ws2tcpip.h>
#include <thread>

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
	
	Log("[%s, %d] accept started\n", ip, port);
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
			Log("Accept Error %u", ::GetLastError());
			continue;
		}

		Log("Accepted %u.%u.%u.%u",
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

void Acceptor::Log(const char* format, ...)
{
	char szpath[256] = { 0, };
	char szbuff[512] = { 0, };
	char szdate[256] = { 0, };
	char sztime[256] = { 0, };

	// 시간 처리
	// https://araikuma.tistory.com/597
	// https://m.blog.naver.com/PostView.nhn?blogId=igazoa2&logNo=220271308803&proxyReferer=https%3A%2F%2Fwww.google.com%2F
	time_t now;
	time(&now);
	tm date;
	localtime_s(&date, &now);
	strftime(szdate, 256, "%Y_%m_%d", &date);
	_strtime_s(sztime, 256);

	_snprintf_s(szbuff, 512, "%s(%s)->", szdate, sztime);

	// 가변인자
	// https://dojang.io/mod/page/view.php?id=577
	// https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/d3xd30zz(v=vs.90)
	va_list marker;
	va_start(marker, format);
	_vsnprintf_s(szbuff + strlen(szbuff), 512 - strlen(szbuff), _TRUNCATE, format, marker);
	va_end(marker);

	sprintf_s(szpath, "./acceptor/Accept_[%s-%u][%s].txt", m_ip, m_port, szdate);

	fwrite(szpath, strlen(szpath), 1, stdout);

	FILE* fp = nullptr;
	auto err = fopen_s(&fp, szpath, "at");

	if (fp != 0)
	{
		fwrite(szbuff, strlen(szbuff), 1, fp);
		fclose(fp);
		fp = NULL;
	}
}