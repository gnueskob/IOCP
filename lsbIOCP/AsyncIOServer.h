#pragma once

#include <vector>
#include <unordered_map>

#include "Utils.h"
#include "Log.h"
#include "Worker.h"
#include "Session.h"
#include "AsyncIOException.h"

using workers = std::vector<std::shared_ptr<Worker>>;

class AsyncIOServer : public IServerController
{
public:
	AsyncIOServer() = delete;
	AsyncIOServer(IServerReceiver* pReceiver, DWORD ioMaxSize, DWORD threadNumber, DWORD sessionNumber,  std::string name);
	~AsyncIOServer();
	void Start();
	void Stop();

	// IServerController
	DWORD postRecv(Session* session) override;
	DWORD postSend() override;
	DWORD disconnectSocket() override;
	DWORD connectSocket() override;
	DWORD registerSokcet() override;

	// Get session map information
	virtual const sessionMap* GetSessionMap() const = 0;

private:
	IServerReceiver*	m_pReceiver;

	HANDLE			m_IOCPHandle;

	size_t			m_IOMaxSize;
	static size_t	IO_MIN_SIZE;

	size_t			m_SessionNumber;
	static size_t	SESSION_MAX_NUMBER;

	size_t		m_ThreadNum;
	workers		m_Workers;

	std::string m_ServerName;
	Log*		m_Log;

	sessionMap*	m_SessionMap;
};