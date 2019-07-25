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
		// ������ recv ��Ŷ ���ۿ� write (packetBufferManager �̿�)
		// ������ recv ��Ŷ ���۸� �о �ϳ��� ��Ŷ ���� �̻� ������ ��� process
		// �ƴ� �� return

		// TODO: ���̺귯�� postRecv/Send, GQCS���� wsabuf ���� packetBuffer�� ��ȯ, write ��� ���η� ������
		sessionDesc.m_pPacketBuffer->Write(data, 0, bytesNumber);

		PacketHeader pktHeader;
		auto pBody = sessionDesc.m_pPacketBuffer->Read(reinterpret_cast<char*>(&pktHeader), PACKET_HEADER_SIZE, GetPacketSize);

		// ���� �ϼ��� ��Ŷ�� ����
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