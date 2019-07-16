#include "AsyncIOServer.h"

DWORD AsyncIOServer::postRecv(Session* session)
{
	m_Log->Write("Post receive");

}

DWORD AsyncIOServer::postSend()
{
	return 0;
}

DWORD AsyncIOServer::disconnectSocket()
{
	return 0;
}

DWORD AsyncIOServer::connectSocket()
{
	return 0;
}

DWORD AsyncIOServer::registerSokcet()
{
	return 0;
}

const sessionMap* AsyncIOServer::GetSessionMap() const
{

}