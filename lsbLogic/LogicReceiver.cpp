#include "LogicMain.h"

namespace lsbLogic
{
	void LogicMain::NotifyClientConnected(SESSIONDESC& sessionDesc) const
	{
		printf("Connected %d\n", sessionDesc.id);
	}

	void LogicMain::NotifyClientDisconnected(INT sessionId) const
	{
		printf("Disconnected %d\n", sessionId);
	}

	void LogicMain::NotifyMessage(SESSIONDESC& sessionDesc, size_t bytesNumber, char* data) const
	{
		int sessionId = sessionDesc.id;
		// ������ recv ��Ŷ ���ۿ� write (packetBufferManager �̿�)
		// ������ recv ��Ŷ ���۸� �о �ϳ��� ��Ŷ ���� �̻� ������ ��� process
		// �ƴ� �� return
	}

	void LogicMain::NotifyServerConnectingResult(SESSIONDESC& sessionDesc, INT requestId, DWORD error) const
	{
		if (error != FALSE)
			printf("connecting fail, error %d\n", error);
		else
			printf("connecting successfully session id : %d, req Id : %d\n", sessionDesc.id, requestId);
	}
}