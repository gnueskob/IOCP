#include "LogicMain.h"
#include "Packet.h"

namespace lsbLogic
{
	void LogicMain::NotifyClientConnected(SESSIONDESC& sessionDesc) const
	{
		PacketInfo packet;
		packet.SessionId = sessionDesc.id;
		packet.PacketId = static_cast<short>(PACKET_ID::NTF_SYS_CONNECT_SESSION);
		m_PacketQueue.push(packet);
	}

	void LogicMain::NotifyClientDisconnected(INT sessionId) const
	{
		PacketInfo packet;
		packet.SessionId = sessionId;
		packet.PacketId = static_cast<short>(PACKET_ID::NTF_SYS_CLOSE_SESSION);
		m_PacketQueue.push(packet);
	}

	void LogicMain::NotifyMessage(SESSIONDESC& sessionDesc, size_t bytesNumber, char* data) const
	{
		int sessionId = sessionDesc.id;
		// 유저의 recv 패킷 버퍼에 write (packetBufferManager 이용)
		// 유저의 recv 패킷 버퍼를 읽어서 하나의 패킷 단위 이상 들어왔을 경우 process
		// 아닐 시 return

		// TODO: 라이브러리 postRecv/Send, GQCS에서 wsabuf 구조 packetBuffer로 전환, write 기능 내부로 돌리기
		sessionDesc.m_pPacketBuffer->Write(data, 0, bytesNumber);

		PacketHeader pktHeader;
		auto pBody = sessionDesc.m_pPacketBuffer->Read(reinterpret_cast<char*>(&pktHeader), PACKET_HEADER_SIZE, GetPacketSize);

		// 아직 완성된 패킷이 없음
		if (pBody == nullptr)
		{
			return;
		}

		PacketInfo packet;
		packet.SessionId = sessionDesc.id;
		packet.PacketId = pktHeader.Id;
		packet.PacketBodySize = pktHeader.PacketSize - PACKET_HEADER_SIZE;
		packet.pData = pBody;

		m_PacketQueue.push(packet);
	}

	void LogicMain::NotifyServerConnectingResult(SESSIONDESC& sessionDesc, INT requestId, DWORD error) const
	{
		if (error != FALSE)
			printf("connecting fail, error %d\n", error);
		else
			printf("connecting successfully session id : %d, req Id : %d\n", sessionDesc.id, requestId);
	}
}