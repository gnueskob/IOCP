#pragma once

#include <string>

namespace lsbLogic
{
	enum class USER_STATE
	{
		DISCONNECTED = 0,
		NONE = 1,
		LOGIN = 2,
		ROOM = 3,
	};

	class User
	{
	public:
		User(const int index) : m_Index(index) {}

		void Clear()
		{
			m_SessionId = -1;
			m_RoomId = -1;
			m_State = USER_STATE::DISCONNECTED;
			m_Id = "";
		}

		void Set(const int sessionId, const char* id)
		{
			m_State = USER_STATE::NONE;
			m_SessionId = sessionId;
			m_Id = id;
		}

		const short GetIndex() const
		{
			return m_Index;
		}

		const int GetSessionId() const
		{
			return m_SessionId;
		}

		const std::string& GetId() const
		{
			return m_Id;
		}

		bool IsCurStateLogin() const
		{
			return m_State == USER_STATE::LOGIN;
		}

		bool IsCurStateRoom() const
		{
			return m_State == USER_STATE::ROOM;
		}

		bool IsCurStateNone() const
		{
			return m_State == USER_STATE::NONE;
		}

		bool IsCurStateDisconnected() const
		{
			return m_State == USER_STATE::DISCONNECTED;
		}

	private:
		short			m_Index = -1;
		short			m_RoomId = -1;
		int				m_SessionId = -1;
		USER_STATE		m_State = USER_STATE::DISCONNECTED;
		std::string		m_Id;
	};
}