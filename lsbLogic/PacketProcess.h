#pragma once

#include "..//lsbIOCP/IServer.h"
#include "Packet.h"
#include "ErrorCode.h"

using ERROR_CODE = lsbLogic::ERROR_CODE;

namespace lsbLogic
{
	class PacketProcess
	{
	public:
		// TODO: 매니저 연결
		void Init(
			IServerReceiver* const pReceiver,
			UserManager* const pUsrMngr,
			ServerConfig* const pConfig,
			ILog* const pLogger);

		void Process(PacketInfo packetInfo);
	};
}