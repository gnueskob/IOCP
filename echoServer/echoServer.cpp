#include "../lsbIOCP/Acceptor.h"
#include "../lsbIOCP/AsyncIOServer.h"
#include "lsbReceiver.h"
#include "../lsbIOCP/PacketBufferManager.h"

int GetPakcetSize(char* packet)
{
	int size = *BytesToType<int>(packet);
	return size;
}

int main()
{
	packetSizeFunc parseFunc = GetPakcetSize;

	// Make custom receiver
	lsbReceiver receiver;

	// Make your server with custom receiver
	AsyncIOServer lsbNetork(&receiver, parseFunc);
	lsbNetork.Start();
	lsbNetork.Join();

	return 0;
}