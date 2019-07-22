#include "SessionManager.h"

// Constructor of SessionManager
// Create session object pool ( [sessionNum] sessions )
// Set unique id of each session and push id to concurrent_queue (session id queue)
SessionManager::SessionManager(INT sessionNum, INT sessionMaxNum, INT ioBufMaxSize, IServerController* pController)
	: m_SessionNumber(sessionNum)
	, m_SessionMaxNumber(sessionMaxNum)
	, m_IOBufMaxSize(ioBufMaxSize)
{
	ThrowErrorIf(sessionNum > sessionMaxNum, SESSION_MAX, "Session number is over max limit");

	m_ConnectedSessionNumber.store(0);
	INT sessionId = 0;
	m_SessionPool.assign(sessionNum, nullptr);
	for (auto& session : m_SessionPool)
	{
		session = new SESSION(ioBufMaxSize, pController);
		session->SetSessionId(sessionId);
		m_SessionIdPool.push(sessionId++);
	}

	Log::GetInstance()->Write(utils::Format("Create %d Sessions succesfully", sessionNum), LOG_LEVEL::DEBUG);
}

// Retrieve available session id and count up total connected session number
bool SessionManager::retrieveId(INT& _out_sessionId)
{
	m_ConnectedSessionNumber++;
	return m_SessionIdPool.try_pop(_out_sessionId);
}

// Return available session id and count up total connected session number
void SessionManager::returnId(INT sessionId)
{
	m_ConnectedSessionNumber--;
	m_SessionIdPool.push(sessionId);
}

// Get session descriptor of session id
SESSIONDESC& SessionManager::GetSessionDescRef(INT sessionId)
{
	return m_SessionPool.at(sessionId)->GetSessionDescRef();
}

// SESSION has atomic member values, so they can not use &(ref) constructor
// https://stackoverflow.com/questions/14182258/c11-write-move-constructor-with-atomicbool-member
// Get session of session id
SESSION* SessionManager::GetSessionPtr(INT sessionId)
{
	return m_SessionPool.at(sessionId);
}

// Post WSARecv
DWORD SessionManager::PostRecv(SESSION* pSession)
{
	if (pSession == nullptr) return WSAEINVAL;

	// TODO: consider CAS structure by checking open flag
	{
		if (pSession->IsOpened() == false) return WSAEINVAL;

		auto lpOverlapped = pSession->GetOverlapped(OP_TYPE::RECV);
		auto& wsabuf = lpOverlapped->wsabuf;

		// session->enterIO();

		// TODO: really needed?
		lpOverlapped->Init();

		// Set type and buffer max size
		lpOverlapped->type = OP_TYPE::RECV;
		wsabuf.len = static_cast<ULONG>(m_IOBufMaxSize);

		DWORD bufferCount = 1;
		DWORD flags = 0;
		DWORD nbytes = 0;
		auto res = WSARecv(
			pSession->GetSocket(),
			&wsabuf,
			bufferCount,
			&nbytes,
			&flags,
			&lpOverlapped->overlapped,
			NULL);

		if (res == SOCKET_ERROR)
		{
			auto error = WSAGetLastError();
			if (error != WSA_IO_PENDING) return error;
		}

		Log::GetInstance()->Write("Posted WSARecv()", LOG_LEVEL::DEBUG);
	}

	return 0;
}

// Post WSASend
DWORD SessionManager::PostSend(SESSION* pSession, size_t length, char* data)
{
	// Check condition
	if (length <= 0 || length > m_IOBufMaxSize) return WSAEMSGSIZE;
	if (length == 0 || data == nullptr) return WSAEINVAL;
	if (pSession == nullptr) return WSAEINVAL;

	// TODO: consider CAS structure by checking open flag
	{
		if (pSession->IsOpened() == false) return WSAEINVAL;

		auto lpOverlapped = pSession->GetOverlapped(OP_TYPE::SEND);
		auto& wsabuf = lpOverlapped->wsabuf;

		// pSession->enterIO();

		// TODO: really needed?
		lpOverlapped->Init();

		// Set type and copy data & length to WSAbuffer
		lpOverlapped->type = OP_TYPE::SEND;
		wsabuf.len = static_cast<ULONG>(length);
		CopyMemory(wsabuf.buf, data, length);

		DWORD bufferCount = 1;
		DWORD flags = 0;
		DWORD nbytes = 0;
		auto res = WSASend(
			pSession->GetSocket(),
			&wsabuf,
			bufferCount,
			&nbytes,
			flags,
			&lpOverlapped->overlapped,
			NULL);

		if (res == SOCKET_ERROR)
		{
			auto error = WSAGetLastError();
			if (error != WSA_IO_PENDING && error != ERROR_SUCCESS) return error;
		}

		Log::GetInstance()->Write("Posted WSARSend()", LOG_LEVEL::DEBUG);
	}

	return 0;
}
