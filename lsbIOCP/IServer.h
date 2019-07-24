#pragma once

#include "Session.h"

class IServerController {
public:
	virtual DWORD SendPacket(const INT sessionId, size_t length, char* data, short headerLength, char* header) = 0;
	virtual DWORD ConnectSocket(INT requestId, const char* ip, u_short port) = 0;
	virtual DWORD DisconnectSocket(const INT sessionId) = 0;
};

class IServerReceiver {
public:
	// multi-thread 환경에서 호출 됨을 명심

	// 클라이언트 소켓 연결 통보
	virtual void NotifyClientConnected(SESSIONDESC& sessionDesc) const = 0;

	// 클라이언트 소켓 연결해제 통보
	virtual void NotifyClientDisconnected(INT sessionId) const = 0;

	// 메시지 수신 통보
	virtual void NotifyMessage(SESSIONDESC& sessionDesc, size_t bytesNumber, char* data) const = 0;

	// 외부 서버 소켓 연결 요청 결과 통보
	virtual void NotifyServerConnectingResult(SESSIONDESC& session, INT requestId, DWORD error) const = 0;
};