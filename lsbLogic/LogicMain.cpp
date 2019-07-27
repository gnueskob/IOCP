#include "..//lsbIOCP/AsyncIONetwork.h"

#include "ConnectedUserManager.h"
#include "UserManager.h"
#include "RoomManager.h"
#include "PacketProcess.h"
#include "LogicMain.h"

namespace lsbLogic
{
	void LogicMain::Start()
	{
		m_pNetwork->Start();
		m_IsRun = true;
	}

	void LogicMain::Stop()
	{
		m_pNetwork->Stop();
		m_IsRun = false;
	}

	void LogicMain::Run()
	{
		m_Log->Write(LV::TRACE, "%s | Run packet proc", __FUNCTION__);
		while (m_IsRun)
		{
			PacketInfo packetInfo;
			if (m_PacketQueue.try_pop(packetInfo) == false)
			{
				m_pConnUserMngr->LoginCheck();
				continue;
			}

			m_pPktProc->Process(packetInfo);
		}
		m_Log->Write(LV::TRACE, "%s | Exit packet proc", __FUNCTION__);
	}

	void LogicMain::Init(ServerConfig serverConfig, LogicConfig logicConfig)
	{
		m_SConfig = serverConfig;
		m_LConfig = logicConfig;

		serverConfig.maxPacketSize = PACKET_MAX_SIZE;
		logicConfig.maxUserNumInRoom = MAX_ROOM_USER_COUNT;

		m_pNetwork = new AsyncIONetwork(this, serverConfig);
		
		m_Log = new Log();
		auto file = std::string("tempLog");
		m_Log->Init(LV::DEBUG, file);

		m_pUserMngr = new UserManager();
		m_pUserMngr->Init(logicConfig.maxUserNum);

		m_pRoomMngr = new RoomManager();
		m_pRoomMngr->Init(this, logicConfig.maxRoomNum, m_Log);

		m_pConnUserMngr = new ConnectedUserManager();
		m_pConnUserMngr->Init(m_pNetwork, serverConfig.sessionNumber, true, m_Log);

		m_pPktProc = new PacketProcess();
		m_pPktProc->Init(this, m_pUserMngr, m_pRoomMngr, serverConfig, m_pConnUserMngr, m_Log);

		m_Log->Write(LOG_LEVEL::INFO, "%s | Init Success", __FUNCTION__);
	}

	void LogicMain::SendMsg(const int sessionId, const short packetId, const short length, char* data)
	{
		auto totalSize = static_cast<short>(PACKET_HEADER_SIZE + length);
		PacketHeader header{ totalSize, packetId, static_cast<unsigned char>(0) };
		m_Log->Write(LV::DEBUG, "%s | packet size : %u, packet id : %u, body length %u", __FUNCTION__, totalSize, packetId, length);
		m_pNetwork->SendPacket(sessionId, length, data, PACKET_HEADER_SIZE, reinterpret_cast<char*>(&header));
		m_Log->Write(LV::TRACE, "%s | Send Packet", __FUNCTION__);
	}

	void LogicMain::ForceClose(const int sessionId)
	{
		m_pNetwork->DisconnectSocket(sessionId);
		m_Log->Write(LV::TRACE, "%s | Close connection", __FUNCTION__);
	}

	void LogicMain::ConnectServer(const int reqId, const char* ip, unsigned short port)
	{
		m_pNetwork->ConnectSocket(reqId, ip, port);
		m_Log->Write(LV::TRACE, "%s | Request connection to server %s - %u", __FUNCTION__, ip, port);
	}
}