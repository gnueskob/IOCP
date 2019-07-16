#pragma once

#include <windows.h>

#include "Session.h"

using sessionMap = std::unordered_map<ULONG_PTR, Session*>;

class IServerController {
public:
	virtual DWORD postRecv(Session* session) = 0;
	virtual DWORD postSend() = 0;
	virtual DWORD disconnectSocket() = 0;
	virtual DWORD connectSocket() = 0;
	virtual DWORD registerSokcet() = 0;

	// Get session map information
	virtual const sessionMap* GetSessionMap() const = 0;
};

class IServerReceiver {
public:
	// multi-thread 환경에서 호출 됨을 명심

	// 클라이언트 소켓 연결 통보
	virtual void NotifyClientConnected() const = 0;

	// 클라이언트 소켓 연결해제 통보
	virtual void NotifyClientDisconnected() const = 0;

	// 메시지 수신 통보
	virtual void NotifyMessage() const = 0;

	// 외부 서버 소켓 연결 요청 결과 통보
	virtual void NotifyServerConnectingResult() const = 0;

	// 외부 서버 소켓 연결해제 통보
	virtual void NotifyServerDisconnect() const = 0;
};