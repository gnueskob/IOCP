#include <chrono>

#include "../../Lib_NetworkIOCP/AsyncIONetwork.h"

#include "ConnectedUserManager.h"
#include "UserManager.h"
#include "RoomManager.h"
#include "PacketProcess.h"
#include "LogicMain.h"

namespace lsbLogic
{
	void LogicMain::Start()
	{
		m_pNetwork->Start();
		m_IsRun = true;

		m_Runner = new std::thread(&LogicMain::Run, this);
		m_ConnUsrMngrRunner = new std::thread(&LogicMain::ConnUsrMngrRun, this);
	}

	void LogicMain::Stop()
	{
		m_pNetwork->Stop();
		m_IsRun = false;

		PacketInfo exitSignal(PACKET_ID::SERVER_EXIT);
		m_PacketQueue.push(exitSignal);
		m_cv.notify_one();
	}

	void LogicMain::Join()
	{
		m_ConnUsrMngrRunner->join();
		m_Runner->join();
		m_pNetwork->Join();
	}

	void LogicMain::ConnUsrMngrRun()
	{
		std::chrono::seconds delay(5);
		while (m_IsRun)
		{
			PacketInfo loginChk(PACKET_ID::SERVER_LOGIN_CHECK);
			m_PacketQueue.push(loginChk);
			m_cv.notify_one();

			std::this_thread::sleep_for(delay);
		}
	}

	void LogicMain::Run()
	{
		m_pLogger->Write(LV::TRACE, "%s | Run packet proc", __FUNCTION__);
		while (m_IsRun)
		{
			std::unique_lock<std::mutex> lock(m_PktProcLock);

			// TODO: condition variable을 사용해서 produce consume 패턴을 이용한 것은 좋으나
			// 매번 lock을 걸어야 하고, 이미 thread-safe한 queue를 사용하는 이점이 없어짐
			// 또한, 매번 job을 추가할 때마다 notify를 보내주는 것도 낭비
			// 단순한 sleep이 더 나을 수 있음
			PacketInfo packetInfo;
			m_cv.wait(lock, [&] { return m_PacketQueue.try_pop(packetInfo); });
			lock.unlock();

			if (packetInfo.PacketId == static_cast<short>(PACKET_ID::SERVER_LOGIN_CHECK))
			{
				m_pConnUserMngr->LoginCheck();
				m_pLogger->Write(LV::DEBUG, "%s | Session login state check proc", __FUNCTION__);
				continue;
			}

			if (packetInfo.PacketId == static_cast<short>(PACKET_ID::SERVER_EXIT))
			{
				break;
			}

			m_pPktProc->Process(packetInfo);
		}
		m_pLogger->Write(LV::TRACE, "%s | Exit packet proc", __FUNCTION__);
	}

	void LogicMain::Init(LogicConfig config)
	{
		m_Config = config;

		NetworkConfig networkConfig =
		{
			config.threadNumber,
			config.sessionNumber,
			config.bufferSize,
			PACKET_HEADER_SIZE,
			PACKET_MAX_SIZE,
			config.ip.c_str(),
			config.port,
			config.name
		};

		m_pNetwork = new AsyncIONetwork(this, networkConfig);

		m_pLogger = new Log();
		auto file = std::string("tempLog");
		m_pLogger->Init(LV::DEBUG, file);

		m_pUserMngr = new UserManager();
		m_pUserMngr->Init(m_Config.maxUserNum);

		m_pRoomMngr = new RoomManager();
		m_pRoomMngr->Init(this, m_Config.maxRoomNum, m_pLogger);

		m_pConnUserMngr = new ConnectedUserManager();
		m_pConnUserMngr->Init(m_pNetwork, m_Config.sessionNumber, true, m_pLogger);

		m_pPktProc = new PacketProcess();
		m_pPktProc->Init(this, m_pUserMngr, m_pRoomMngr, m_pConnUserMngr, m_pLogger);

		m_pLogger->Write(LOG_LEVEL::INFO, "%s | Init Success", __FUNCTION__);
	}

	/*
	void LogicMain::SendMsg(const int sessionId, const short packetId, const short length, char* pData, Message* pMsg)
	{
		// TODO: packet header를 각 res packet에 상속시켜 사용 -> Write 두번 할 필요가 없어짐
		auto totalSize = static_cast<short>(PACKET_HEADER_SIZE + length);
		PacketHeader header{ totalSize, packetId, static_cast<unsigned char>(0) };
		m_pLogger->Write(LV::DEBUG, "%s | packet size : %u, packet id : %u, body length %u", __FUNCTION__, totalSize, packetId, length);
		m_pNetwork->SendPacket(sessionId, length, pData, pMsg, PACKET_HEADER_SIZE, reinterpret_cast<char*>(&header));
		m_pLogger->Write(LV::TRACE, "%s | Send Packet", __FUNCTION__);
	}
	*/

	void LogicMain::SendProto(const int sessionId, const short packetId, Message* pMsg)
	{
		auto bodyLength = static_cast<short>(pMsg->ByteSize());
		auto totalSize = static_cast<short>(PACKET_HEADER_SIZE + bodyLength);
		PacketHeader header{ totalSize, packetId, static_cast<unsigned char>(0) };
		m_pLogger->Write(LV::DEBUG, "%s | packet size : %u, packet id : %u, body length %u", __FUNCTION__, totalSize, packetId, bodyLength);
		
		// TODO: 매 실행마다 std::function 셋팅이 필요하므로 미리 세팅해주는 작업이 필요 - Init 즈음에 함수 미리 가지고 참조만 하게끔 변경하기
		auto err = m_pNetwork->SendPacket(
			sessionId
			, bodyLength
			, nullptr
			, PACKET_HEADER_SIZE
			, reinterpret_cast<char*>(&header)
			, [&pMsg](char* writePos, int bodyLength) -> bool {
				io::ArrayOutputStream os(writePos, bodyLength);
				return pMsg->SerializeToZeroCopyStream(&os);
			});

		if (err != NET_ERROR_CODE::NONE)
		{
			m_pLogger->Write(LV::ERR, "%s | Can not send packet", __FUNCTION__);
		}
		else
		{
			m_pLogger->Write(LV::TRACE, "%s | Send Proto", __FUNCTION__);
		}
	}

	void LogicMain::ForceClose(const int sessionId)
	{
		m_pNetwork->DisconnectSocket(sessionId);
		m_pLogger->Write(LV::TRACE, "%s | Close connection", __FUNCTION__);
	}

	void LogicMain::ConnectServer(const int reqId, const char* ip, unsigned short port)
	{
		m_pNetwork->ConnectSocket(reqId, ip, port);
		m_pLogger->Write(LV::TRACE, "%s | Request connection to server %s - %u", __FUNCTION__, ip, port);
	}
}