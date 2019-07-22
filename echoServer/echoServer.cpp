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
	const INT sessionMaxNum = 3000;
	const INT ioMaxBufferSize = 1024;

	// Make custom receiver
	lsbReceiver receiver;

	// Make your server with custom receiver
	AsyncIOServer lsbServer(&receiver, ioMaxBufferSize, threadNumber, sessionNumber, sessionMaxNum, serverName, ip, port);
	lsbServer.Start();
	lsbServer.Join();

	return 0;
}