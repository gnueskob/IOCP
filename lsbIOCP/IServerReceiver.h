#pragma once

namespace lsbIOCP {

	class IServerReceiver {
	public:
		// multi-thread ȯ�濡�� ȣ�� ���� ���

		// Ŭ���̾�Ʈ ���� ���� �뺸
		virtual void notifyClientConnected() const = 0;

		// Ŭ���̾�Ʈ ���� �������� �뺸
		virtual void notifyClientDisconnected() const = 0;

		// �޽��� ���� �뺸
		virtual void notifyMessage() const = 0;

		// �ܺ� ���� ���� ���� ��û ��� �뺸
		virtual void notifyServerConnectingResult() const = 0;

		// �ܺ� ���� ���� �������� �뺸
		virtual void notifyServerDisconnect() const = 0;
	};

}