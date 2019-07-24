#include "../lsbIOCP/Acceptor.h"
#include "../lsbIOCP/AsyncIOServer.h"
#include "../lsbIOCP/PacketBufferManager.h"
#include "lsbReceiver.h"

int GetPakcetSize(char* packet)
{
	int size = *BytesToType<int>(packet);
	return size;
}

int main()
{
	const INT threadNumber = 2;

	const INT sessionNumber = 1000;
	const INT ioMaxSize = 1024;

	const int bufferSize = 1024;
	const int headerSize = 5;
	const int maxPacketSize = 50;

	const char* const ip = "127.0.0.1";
	const u_short port = 23452;
	const std::string name = "SampleServer";

	ServerConfig config =
	{
		threadNumber,

		sessionNumber,
		ioMaxSize,

		bufferSize,
		headerSize,
		maxPacketSize,

		ip, port, name,
	};

	packetSizeFunc parseFunc = GetPakcetSize;

	// Make custom receiver
	lsbReceiver receiver;

	// Make your server with custom receiver
	AsyncIOServer lsbNetork(&receiver, config, parseFunc);
	lsbNetork.Start();
	lsbNetork.Join();

	return 0;
}