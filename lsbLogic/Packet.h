#pragma once

#include "PacketID.h"
#include "ErrorCode.h"

namespace lsbLogic
{
#pragma pack(push, 1)
	class PacketInfo
	{
	public:
		int SessionId = -1;
		short PacketId = -1;
		short PacketBodySize = 0;
		char* pData = nullptr;
	};

	class PacketHeader
	{
	private:
		short PacketSize;
		short Id;
		unsigned char Reserved;
	};
	const int PACKET_HEADER_SIZE = sizeof(PacketHeader);

	class PacketBase
	{
	public:
		void SetErrorCode(ERROR_CODE error)
		{
			ErrorCode = static_cast<short>(error);
		}
	private:
		short ErrorCode = static_cast<short>(ERROR_CODE::NONE);
	};

	// Packet class for login req, res
	const int MAX_USER_ID_SIZE = 16;
	const int MAX_USER_PW_SIZE = 16;
	class PacketLoginReq
	{
		char szID[MAX_USER_ID_SIZE + 1] = { 0, };
		char szPW[MAX_USER_PW_SIZE + 1] = { 0, };
	};

	class PacketLoginRes : public PacketBase
	{
	};

	// Packet class for entering room
	const int MAX_ROOM_TITLE_SIZE = 16;
	class PacketRoomEnterReq
	{
		bool IsCreate;
		short RoomIndex;
		wchar_t RoomTitle[MAX_ROOM_TITLE_SIZE + 1];
	};

	class PacketRoomEnterRes : public PacketBase
	{
	};

	class PacketRoomEnterNtf
	{
		char UserId[MAX_USER_ID_SIZE + 1] = { 0, };
	};

	// Packet class for leaving room
	class PacketRoomLeaveReq
	{
	};

	class PacketRoomLeaveRes : public PacketBase
	{
	};

	class PacketRoomLeaveNtf
	{
		char UserId[MAX_USER_ID_SIZE + 1] = { 0, };
	};

	// Packet class for chatting in room
	const int MAX_ROOM_CHAT_MSG_SIZE = 256;
	class PacketRoomChatReq
	{
		wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE + 1] = { 0, };
	};

	class PacketRoomChatRes : public PacketBase
	{
	};

	class PacketRoomChatNtf
	{
		char UserId[MAX_USER_ID_SIZE + 1] = { 0, };
		wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE + 1] = { 0, };
	};

	// Packet class for echo
	const int DEV_ECHO_DATA_MAX_SIZE = 1024;
	class PacketEchoReq
	{
		short DataSize;
		char Data[DEV_ECHO_DATA_MAX_SIZE];
	};

	class PacketEchoRes : public PacketBase
	{
		short DataSize;
		char Data[DEV_ECHO_DATA_MAX_SIZE];
	};
#pragma pop
}