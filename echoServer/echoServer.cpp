#include "../lsbIOCP/Acceptor.h"
#include "../lsbIOCP/AsyncIOServer.h"
#include "lsbReceiver.h"
#include "../lsbIOCP/PacketBufferManager.h"

int main()
{
	const char* ip = "127.0.0.1";
	const unsigned short port = 23452;
	const std::string serverName = "simpleEchoServer";

	const INT threadNumber = 2;
	const INT sessionNumber = 1000;

	// config
	const INT SESSION_MAX_NUM = 3000;
	const INT IO_MAX_BUFFER_SIZE = 1024;
	const INT IO_MIN_SIZE = 1024;

	// Make custom receiver
	lsbReceiver receiver;

	// Make your server with custom receiver
	AsyncIOServer lsbServer(&receiver, IO_MAX_BUFFER_SIZE, IO_MIN_SIZE, threadNumber, sessionNumber, SESSION_MAX_NUM, serverName, ip, port);
	lsbServer.Start();
	lsbServer.Join();

	return 0;
}