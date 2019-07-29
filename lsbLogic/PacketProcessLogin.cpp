#include <tuple>

#include "Common/ErrorCode.h"
#include "Common/Packet.h"
#include "ConnectedUserManager.h"
#include "User.h"
#include "UserManager.h"
#include "RoomManager.h"
#include "PacketProcess.h"

namespace lsbLogic
{
	ERROR_CODE PacketProcess::Login(PacketInfo packet)
	{
		/*
		PacketLoginRes resPkt;
		auto reqPkt = reinterpret_cast<PacketLoginReq*>(packet.pData);
		
		auto err = m_pUserMngr->AddUser(packet.SessionId, reqPkt->szID);

		auto packetId = static_cast<short>(PACKET_ID::LOGIN_RES);
		auto data = reinterpret_cast<char*>(&resPkt);

		if (err != ERROR_CODE::NONE)
		{
			resPkt.SetErrorCode(err);
			m_pLogicMain->SendMsg(packet.SessionId, packetId, sizeof(resPkt), data, nullptr);
			return err;
		}

		m_pConnectedUserManager->SetLogin(packet.SessionId);
		
		m_Log->Write(LV::DEBUG, "%s | Login. id : %s, session Id : %d", __FUNCTION__, reqPkt->szID, packet.SessionId);
		resPkt.SetErrorCode(err);
		m_pLogicMain->SendMsg(packet.SessionId, packetId, sizeof(resPkt), data, nullptr);
		*/

		lsbProto::LoginReq reqPkt;

		io::ArrayInputStream is(packet.pData, packet.PacketBodySize);
		reqPkt.ParseFromZeroCopyStream(&is);

		auto err = m_pUserMngr->AddUser(packet.SessionId, reqPkt.id().c_str());

		lsbProto::LoginRes resPkt;

		auto packetId = static_cast<short>(PACKET_ID::LOGIN_RES);
		resPkt.set_res(static_cast<google::protobuf::int32>(err));
		auto sendSize = static_cast<short>(resPkt.ByteSize());
		auto pProto = dynamic_cast<Message*>(&resPkt);

		if (err != ERROR_CODE::NONE)
		{
			m_pLogicMain->SendMsg(packet.SessionId, packetId, sendSize, nullptr, pProto);
			return err;
		}

		m_pConnectedUserManager->SetLogin(packet.SessionId);

		m_Log->Write(LV::DEBUG, "%s | Login. id : %s, session Id : %d", __FUNCTION__, reqPkt.id().c_str(), packet.SessionId);
		m_pLogicMain->SendMsg(packet.SessionId, packetId, sendSize, nullptr, pProto);

		return ERROR_CODE::NONE;
	}

	ERROR_CODE PacketProcess::Logout(PacketInfo packet)
	{
		PacketLogoutRes resPkt;

		auto packetId = static_cast<short>(PACKET_ID::LOGOUT_RES);
		auto data = reinterpret_cast<char*>(&resPkt);

		auto [err, pUser] = m_pUserMngr->GetUser(packet.SessionId);

		if (err != ERROR_CODE::NONE)
		{
			resPkt.SetErrorCode(err);
			m_pLogicMain->SendMsg(packet.SessionId, packetId, sizeof(resPkt), data, nullptr);
			return err;
		}

		auto pRoom = std::get<1>(m_pRoomMngr->GetRoom(pUser->GetRoomIndex()));

		if (pRoom)
		{
			pRoom->LeaveUser(pUser->GetIndex());
			pRoom->NotifyLeaveUserInfo(pUser->GetIndex());

			m_Log->Write(LOG_LEVEL::DEBUG, "%s | Logout. sessionIndex(%d). Room Out", __FUNCTION__, packet.SessionId);
		}

		m_pUserMngr->RemoveUser(packet.SessionId);

		m_pConnectedUserManager->SetLogout(packet.SessionId);

		m_Log->Write(LV::DEBUG, "%s | Logout. session id : %d", __FUNCTION__, packet.SessionId);
		resPkt.SetErrorCode(err);
		m_pLogicMain->SendMsg(packet.SessionId, packetId, sizeof(resPkt), data, nullptr);

		return ERROR_CODE::NONE;
	}
}