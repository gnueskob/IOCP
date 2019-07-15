#pragma once

namespace lsbIOCP {

	class IServerReceiver {
	public:
		// multi-thread 환경에서 호출 됨을 명심

		// 클라이언트 소켓 연결 통보
		virtual void notifyClientConnected() const = 0;

		// 클라이언트 소켓 연결해제 통보
		virtual void notifyClientDisconnected() const = 0;

		// 메시지 수신 통보
		virtual void notifyMessage() const = 0;

		// 외부 서버 소켓 연결 요청 결과 통보
		virtual void notifyServerConnectingResult() const = 0;

		// 외부 서버 소켓 연결해제 통보
		virtual void notifyServerDisconnect() const = 0;
	};

}