#pragma once

#include "..//lsbIOCP/IServer.h"
#include "Packet.h"

namespace lsbLogic
{
	class LogicMain : public IServerReceiver
	{
	public:
		ServerConfig m_Config;

	public:
		void Start();

		// Manager pointer
		void SendMsg(const int sessionId, const short packetId, const short length, char* data);

	private:
		/**************************************** IServerReceiver ****************************************/
		// Triggered when client socket is connected
		void NotifyClientConnected(SESSIONDESC& sessionDesc) const override;

		// Triggered when socket is disconnected
		void NotifyClientDisconnected(INT sessionId) const override;

		// Triggered when server get message from client
		void NotifyMessage(SESSIONDESC& sessionDesc, size_t bytesNumber, char* data) const override;

		// Triggered when the job of connecting to other server is completed
		void NotifyServerConnectingResult(SESSIONDESC& session, INT requrestId, DWORD error) const override;

	private:
		IServerController* m_pController;
	};
}