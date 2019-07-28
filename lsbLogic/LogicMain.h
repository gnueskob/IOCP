#pragma once

#include <concurrent_queue.h>

#include "../lsbIOCP/Struct.h"

#include "Packet.h"
#include "LogicConfig.h"

class Log;
class AsyncIONetwork;

namespace lsbLogic
{
	class UserManager;
	class RoomManager;
	class ConnectedUserManager;
	class PacketProcess;

	class LogicMain : public INetworkReceiver
	{
	public:
		ServerConfig m_Config;

	public:
		void Start();
		void Stop();
		void Run();

		// Manager pointer
		void Init(ServerConfig m_SConfig, LogicConfig m_LConfig);

		void SendMsg(const int sessionId, const short packetId, const short length, char* data);
		void ForceClose(const int sessionId);
		void ConnectServer(const int reqId, const char* ip, unsigned short port);

	private:
		/**************************************** INetworkReceiver ****************************************/
		// Triggered when client socket is connected
		void NotifyClientConnected(const int sessionId) override;

		// Triggered when socket is disconnected
		void NotifyClientDisconnected(const int sessionId) override;

		// Triggered when server get message from client
		bool NotifyMessage(const int sessionId, const int nBytes, char* const pData) override;

		// Triggered when the job of connecting to other server is completed
		void NotifyServerConnectingResult(const int sessionId, const int requrestId, const NET_ERROR_CODE error) override;

	private:
		AsyncIONetwork* m_pNetwork;
		UserManager* m_pUserMngr;
		RoomManager* m_pRoomMngr;
		ConnectedUserManager* m_pConnUserMngr;
		PacketProcess* m_pPktProc;

		ServerConfig m_SConfig;
		LogicConfig m_LConfig;

		bool m_IsRun = false;

		Concurrency::concurrent_queue<PacketInfo> m_PacketQueue;

		Log* m_Log;
	};
}