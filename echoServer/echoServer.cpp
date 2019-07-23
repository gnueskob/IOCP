#include "../lsbIOCP/Acceptor.h"
#include "../lsbIOCP/AsyncIOServer.h"
#include "lsbReceiver.h"
#include "../lsbIOCP/PacketBufferManager.h"

int main()
{
	// config
	const INT IO_MIN_SIZE = 1024;
	const INT IO_MAX_BUFFER_SIZE = 1024;
	const INT threadNumber = 2;
	const INT sessionNumber = 1000;
	const INT SESSION_MAX_NUM = 3000;
	const char* ip = "127.0.0.1";
	const unsigned short port = 23452;
	const std::string serverName = "simpleEchoServer";

	const ServerConfig config
	{
		IO_MIN_SIZE,
		IO_MAX_BUFFER_SIZE,
		threadNumber,
		sessionNumber,
		SESSION_MAX_NUM,
		ip,
		port,
		serverName
	};

	// Make custom receiver
	lsbReceiver receiver;

	// Make your server with custom receiver
	AsyncIOServer lsbServer(&receiver, config);
	lsbServer.Start();
	lsbServer.Join();

	return 0;
}