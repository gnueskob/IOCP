﻿using System;
using System.Text;
using System.Collections.Generic;

namespace echoClient_csharp
{
    public partial class client
    {
        Dictionary<PACKET_ID, Action<byte[]>> PacketFuncDic = new Dictionary<PACKET_ID, Action<byte[]>>();

        void SetPacketHandler()
        {
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ECHO_RES, PacketProcess_Echo);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ERROR_NTF, PacketProcess_ErrorNotify);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_LOGIN_RES, PacketProcess_LoginResponse);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_ENTER_RES, PacketProcess_RoomEnterResponse);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_ENTER_NEW_USER_NTF, PacketProcess_RoomNewUserNotify);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_USER_LIST_NTF, PacketProcess_RoomUserListNotify);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_LEAVE_RES, PacketProcess_RoomLeaveResponse);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_LEAVE_USER_NTF, PacketProcess_RoomLeaveUserNotify);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_CHAT_RES, PacketProcess_RoomChatResponse);
            PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_CHAT_NTF, PacketProcess_RoomChatNotify);
            //PacketFuncDic.Add(PACKET_ID.PACKET_ID_ROOM_RELAY_NTF, PacketProcess_RoomRelayNotify);
        }

        void PacketProcess(PacketData packet)
        {
            var packetType = (PACKET_ID)packet.PacketID;
            // Log.Write("RawPacket: " + packet.PacketID.ToString() + ", " + PacketDump.Bytes(packet.BodyData));

            if (PacketFuncDic.ContainsKey(packetType))
            {
                PacketFuncDic[packetType](packet.BodyData);
            }
            else
            {
                Log.Write("Unknown Packet Id: " + packet.PacketID.ToString());
            }
        }

        void PacketProcess_Echo(byte[] bodyData)
        {
            string body = Encoding.UTF8.GetString(bodyData);
            Log.Write($"Echo Res : {body}");
        }

        void PacketProcess_ErrorNotify(byte[] bodyData)
        {
            var notifyPkt = new ErrorNtfPacket();
            notifyPkt.FromBytes(bodyData);

            Log.Write($"Error:  {notifyPkt.Error}");
        }

        void PacketProcess_LoginResponse(byte[] bodyData)
        {
            var responsePkt = new LoginResPacket();
            responsePkt.FromBytes(bodyData);

            Log.Write($"로그인 결과:  {(ERROR_CODE)responsePkt.Result}");

            if ((ERROR_CODE)responsePkt.Result == ERROR_CODE.ERROR_NONE)
            {
                btnLogin.Enabled = false;
                btnLogout.Enabled = true;
                btnEnter.Enabled = true;
                btnLeave.Enabled = false;
                btnCreate.Enabled = true;
            }
        }

        void PacketProcess_RoomEnterResponse(byte[] bodyData)
        {
            var responsePkt = new RoomEnterResPacket();
            responsePkt.FromBytes(bodyData);

            Log.Write($"방 입장 결과:  {(ERROR_CODE)responsePkt.Result}");

            if ((ERROR_CODE)responsePkt.Result == ERROR_CODE.ERROR_NONE)
            {
                curRoomNumberLabel.Text = responsePkt.RoomIndex.ToString();
                roomLabel.Text = responsePkt.RoomTitle;
                btnCreate.Enabled = false;
                btnEnter.Enabled = false;
                btnLeave.Enabled = true;
            }
        }

        void PacketProcess_RoomNewUserNotify(byte[] bodyData)
        {
            var notifyPkt = new RoomNewUserNtfPacket();
            notifyPkt.FromBytes(bodyData);

            AddRoomUserList(notifyPkt.UserUniqueId, notifyPkt.UserID);

            Log.Write($"방에 새로 들어온 유저 받음");
        }

        void PacketProcess_RoomUserListNotify(byte[] bodyData)
        {
            var notifyPkt = new RoomUserListNtfPacket();
            notifyPkt.FromBytes(bodyData);

            for (int i = 0; i < notifyPkt.UserCount; ++i)
            {
                AddRoomUserList(notifyPkt.UserUniqueIdList[i], notifyPkt.UserIDList[i]);
            }

            Log.Write($"방의 기존 유저 리스트 받음");
        }

        void PacketProcess_RoomLeaveResponse(byte[] bodyData)
        {
            var responsePkt = new RoomLeaveResPacket();
            responsePkt.FromBytes(bodyData);

            Log.Write($"방 나가기 결과:  {(ERROR_CODE)responsePkt.Result}");

            if ((ERROR_CODE)responsePkt.Result == ERROR_CODE.ERROR_NONE)
            {
                ClearRoomInfo();
                btnCreate.Enabled = true;
                btnEnter.Enabled = true;
                btnLeave.Enabled = false;
            }
        }

        void PacketProcess_RoomLeaveUserNotify(byte[] bodyData)
        {
            var notifyPkt = new RoomLeaveUserNtfPacket();
            notifyPkt.FromBytes(bodyData);

            RemoveRoomUserList(notifyPkt.UserUniqueId);

            Log.Write($"방에서 나간 유저 받음");
        }

        void PacketProcess_RoomChatResponse(byte[] bodyData)
        {
            var responsePkt = new RoomChatResPacket();
            responsePkt.FromBytes(bodyData);
            Log.Write($"방 채팅 요청 결과:  {(ERROR_CODE)responsePkt.Result}", LOG_LEVEL.ERROR);
        }

        void PacketProcess_RoomChatNotify(byte[] bodyData)
        {
            var responsePkt = new RoomChatNtfPacket();
            responsePkt.FromBytes(bodyData);

            AddRoomChatMessageList(responsePkt.UserUniqueId, responsePkt.Message);
        }
    }
}
