#include "../lsbIOCP/Acceptor.h"
#include "../lsbIOCP/AsyncIOServer.h"
#include "../lsbIOCP/PacketBufferManager.h"

#include "LogicMain.h"

namespace lsbLogic
{
	void LogicMain::Start()
	{
		m_Config.threadNumber = 2;

		m_Config.sessionNumber = 1000;
		m_Config.ioMaxSize = 1024;

		m_Config.bufferSize = 1024;
		m_Config.headerSize = PACKET_HEADER_SIZE;
		m_Config.maxPacketSize = PACKET_MAX_SIZE;

		m_Config.ip = "127.0.0.1";
		m_Config.port = 23452;
		m_Config.name = "SampleServer";

		packetSizeFunc parseFunc = GetPakcetSize;

		// Make your server with custom receiver
		AsyncIOServer lsbNetork(this, m_Config, parseFunc);
		lsbNetork.Start();
	}

	void LogicMain::SendMsg(const int sessionId, const short packetId, const short length, char* data)
	{
		auto totalSize = static_cast<short>(PACKET_HEADER_SIZE + length);
		PacketHeader header{ totalSize, packetId, static_cast<unsigned char>(0) };
		m_pController->SendPacket(sessionId, length, data, PACKET_HEADER_SIZE, reinterpret_cast<char*>(&header));
	}
}