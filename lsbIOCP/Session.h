#pragma once

#include "Struct.h"
#include "PacketBufferManager.h"

class SessionConfig
{
public:
	INT ioBufMaxSize;
	IServerController* pController;
};

// Session struct including Session descriptor
class SESSION
{
public:
	SESSION() = default;
	SESSION(SessionConfig sessionConfig, PacketBufferConfig pktBufferConfig)
	{
		m_SessionDesc.pController = sessionConfig.pController;
		m_pOverlappedRecv = new OVERLAPPED_EX(sessionConfig.ioBufMaxSize);
		m_pOverlappedSend = new OVERLAPPED_EX(sessionConfig.ioBufMaxSize);
		m_pOverlappedConn = new OVERLAPPED_EX(0);
		m_RefCount.store(0);
		m_IsOpened.store(false);

		m_SessionDesc.m_pPacketBuffer->Init(pktBufferConfig);
	}
	~SESSION()
	{
		delete m_pOverlappedConn;
		delete m_pOverlappedRecv;
		delete m_pOverlappedSend;
	}

	SOCKET GetSocket() const
	{
		return m_SocketId;
	}

	void SetController(IServerController* pController)
	{
		m_SessionDesc.pController = pController;
	}

	void SetSessionId(INT id)
	{
		m_SessionDesc.id = id;
	}

	INT GetSessionId()
	{
		return m_SessionDesc.id;
	}

	void InitOverlapped(OP_TYPE type)
	{
		switch (type)
		{
		default:
		case OP_TYPE::CONN: m_pOverlappedConn->Init(); break;
		case OP_TYPE::RECV: m_pOverlappedRecv->Init(); break;
		case OP_TYPE::SEND: m_pOverlappedSend->Init(); break;
		}
	}

	OVERLAPPED_EX* GetOverlapped(OP_TYPE type)
	{
		switch (type)
		{
		default:
		case OP_TYPE::CONN: return m_pOverlappedConn;
		case OP_TYPE::RECV: return m_pOverlappedRecv;
		case OP_TYPE::SEND: return m_pOverlappedSend;
		}
	}

	SESSIONDESC& GetSessionDescRef()
	{
		return m_SessionDesc;
	}

	void SetSocket(SOCKET socket)
	{
		m_SocketId = socket;
	}

	bool Open()
	{
		bool open = false;
		return m_IsOpened.compare_exchange_strong(open, true);
	}

	bool Close()
	{
		bool open = true;
		return m_IsOpened.compare_exchange_strong(open, false);
	}

	void EnterIO()
	{
		m_RefCount++;
	}

	void ExitIO()
	{
		m_RefCount--;
	}

	bool IsOpened()
	{
		return m_IsOpened.load();
	}

private:
	SESSIONDESC			m_SessionDesc;

	SOCKET				m_SocketId = 0;

	// atomic is not copyable or movable
	// atomic(const atomic&) = delete;
	// atomic& operator=(const atomic&) = delete;
	std::atomic_int		m_RefCount;	// ref count for pending IO to check before return unused session to pool
	std::atomic_bool	m_IsOpened;

	std::mutex			m_SendLock;

	OVERLAPPED_EX* m_pOverlappedSend;
	OVERLAPPED_EX* m_pOverlappedRecv;
	OVERLAPPED_EX* m_pOverlappedConn;
};