#pragma once

#include <winsock2.h>

#include <atomic>
#include <mutex>
#include <string>

enum OP_TYPE { RECV, SEND, CONN };

// Overlapped extended struct
class OVERLAPPED_EX
{
public:
	OVERLAPPED_EX()
	{
		Init(); 
		wsabuf.buf = nullptr; 
	}

	OVERLAPPED_EX(INT maxLength) : maxLength(maxLength)
	{
		Init();
		if (0 < maxLength)
		{
			wsabuf.buf = new char[maxLength];
		}
	}

	~OVERLAPPED_EX()
	{
		if (0 < maxLength)
		{
			delete[] wsabuf.buf;
		}
	}

	void Init()
	{
		ZeroMemory(&overlapped, sizeof(overlapped));
		wsabuf.len = 0;
	}

public:
	OVERLAPPED		overlapped;
	WSABUF			wsabuf;
	OP_TYPE			type = OP_TYPE::RECV;
	INT				maxLength = 0;			// Socket buffer max length // TODO: 없어도 괜찮지 않나?
	INT				requesterId = -1;		// [요청자가 건네는 구분값] for connectSocket()
};

/***********************************************************************************************************/

class IServerController;
// Session descriptor (used in receiver)
// Users manipluate only this, when they need session information
class SESSIONDESC
{
public:
	SESSIONDESC() 
	{ 
		ZeroMemory(&tick, sizeof(tick));
		m_pPacketBuffer = new PacketBufferManager();
	};
	SESSIONDESC(IServerController* pCrtl) : pController(pCrtl) 
	{
		ZeroMemory(&tick, sizeof(tick));
		m_pPacketBuffer = new PacketBufferManager();
	}

	bool CheckTick(SESSIONDESC& desc) const 
	{
		return this->tick.QuadPart == desc.tick.QuadPart; 
	}

public:
	INT				id = -1;
	LARGE_INTEGER	tick;
	IServerController* pController = nullptr;

	PacketBufferManager* m_pPacketBuffer;
};