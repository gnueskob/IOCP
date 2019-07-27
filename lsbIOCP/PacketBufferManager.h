#pragma once

#include <windows.h>

#include <functional>

using packetSizeFunc = std::function<int(char*)>;

class PacketBufferConfig
{
public:
	const int bufferSize;
	const int headerSize;
	const int maxPacketSize;
};

class PacketBufferManager
{
public:
	PacketBufferManager() 
		: m_ReadPos(0)
		, m_WritePos(0)
		, m_BufferSize(0)
		, m_HeaderSize(0)
		, m_MaxPacketSize(0)
		, m_pPacketData(nullptr) {}

	~PacketBufferManager()
	{
		delete[] m_pPacketData;
	}

	bool Init(PacketBufferConfig config)
	{
		if (config.bufferSize < (config.maxPacketSize * 2) || config.headerSize < 0 || config.maxPacketSize < 1)
		{
			// TODO: throw
			return false;
		}

		m_PrevReadPos = 0;
		m_ReadPos = 0;
		m_WritePos = 0;
		m_BufferSize = config.bufferSize;
		m_HeaderSize = config.headerSize;
		m_MaxPacketSize = config.maxPacketSize;
		m_pPacketData = new char[config.bufferSize];

		return true;
	}

	void Clear()
	{
		m_WritePos = 0;
		m_ReadPos = 0;
		m_PrevReadPos = 0;
	}

	// Write n-bytes to packet buffer
	// and increase write pointer in packet buffer to write data at that time
	bool Write(char* pData, int startIndex, int size, bool relocate = true)
	{
		if (pData == nullptr)
		{
			return false;
		}

		int remainingBufferSize = m_BufferSize;

		// �����Ͱ� ���� �����־ ���� Ŀ���� ���� ������ ���ư� ����
		if (m_WritePos < m_PrevReadPos)
		{
			remainingBufferSize = m_PrevReadPos - m_WritePos;
		}
		else
		{
			remainingBufferSize = m_BufferSize - m_WritePos;
		}

		// ���� �����͵��� ����� ����ó�� ���ϰ� �ְų�, �ִ� ��Ŷ ũ�� �̻��� ��û�� �� ��
		if (remainingBufferSize < size)
		{
			return false;
		}

		CopyMemory(m_pPacketData + m_WritePos, pData + startIndex, size);
		m_WritePos += size;

		// Ŀ�� ��ġ ������ ó�� ����
		if (relocate == false)
		{
			return true;
		}

		// ��Ŷ�� �� ������ �����ؼ� Ŀ���� ������ �Űܾ� ��
		// Write�� �� �ִ� ũ�Ⱑ �ִ� ũ�� ���� ������ Ŀ�� ��ġ �ʱ�ȭ
		auto writableSize = m_BufferSize - m_WritePos;
		if (writableSize < m_MaxPacketSize)
		{
			// ó������ �����͵��� ������ ���ϰ� �ִ� ��
			// ������ ���� ���� Write �۾��� ���ж�� �Ǵ�
			if (m_PrevReadPos == 0)
			{
				return false;
			}

			// m_ReadPos, m_PrevReadPos�� �׻� m_WrtiePos���� �ռ����� �ʰ�
			// �׻� Write �� Read, ReadComplete ������ ȣ��� ����

			// Ŀ���� �� ������ �ű��.
			m_WritePos = 0;
		}

		return true;
	}

	// Read n-bytes to destination.
	// Before copy data to dest, dest array size will be checked 
	// whether it's size is bigger than packet size being read
	char* Read(int length, bool relocate = true)
	{
		auto readPos = m_pPacketData + m_ReadPos;
		m_ReadPos += length;

		// Write�� ����������, ���� �� ���� ���� ũ�Ⱑ ��Ŷ �ִ� ũ�⺸�� ������ Ŀ�� ��ġ �ʱ�ȭ
		auto readableSize = m_BufferSize - m_ReadPos;
		if (relocate && readableSize < m_MaxPacketSize)
		{
			m_ReadPos = 0;
		}

		return readPos;
	}

	// ���� �����͸� ����ϰ� �ش� ũ�⸦ �����ϱ� ���� Ŀ�� ��ġ ������
	void ReadComplete(int length)
	{
		m_PrevReadPos += length;

		// ���������� ���� ���� ũ�� �˻� �� �ʱ�ȭ
		auto readableSize = m_BufferSize - m_PrevReadPos;
		if (readableSize < m_MaxPacketSize)
		{
			m_PrevReadPos = 0;
		}
	}

	void IncreseReadPos(int length)
	{
		m_ReadPos += length;
	}

	bool IncreseWrtiePos(int length)
	{
		m_WritePos += length;
		auto writableSize = m_BufferSize - m_WritePos;
		if (writableSize < m_MaxPacketSize)
		{
			if (m_PrevReadPos == 0)
			{
				return false;
			}
			m_WritePos = 0;
		}
		return true;
	}

	char* ReadCurret()
	{
		return m_pPacketData + m_ReadPos;
	}

	char* WriteCurrent()
	{
		return m_pPacketData + m_WritePos;
	}

	// �� ���� ���� �� �ִ� �������� �ִ� ũ�� = ��Ŷ�� �ִ� ũ��
	int MaxWriteLegnth()
	{
		return m_MaxPacketSize;
	}

	int ReablableLength()
	{
		return m_WritePos - m_ReadPos;
	}

	// If write pointer is close to end (i.e., packet buffer is nearly full),
	// pull foward pakcet data on the portion of buffer that alredy read
	void PreventBufferOverflow()
	{
		// Data size that can be read
		int readableSize = m_WritePos - m_ReadPos;
		int WritableSize = m_BufferSize - m_WritePos;
		if (WritableSize < m_MaxPacketSize)
		{
			memmove_s(m_pPacketData, m_BufferSize, m_pPacketData + m_ReadPos, readableSize);
			m_ReadPos = 0;
			m_WritePos = readableSize;
		}
	}

protected:
	char*	m_pPacketData;
	int		m_BufferSize;
	int		m_PrevReadPos = 0;
	int		m_ReadPos = 0;
	int		m_WritePos = 0;

	int		m_HeaderSize = 0;
	int		m_MaxPacketSize = 0;
};

// Function for getting size of packet in header
// Because packet and header structure is decided by user,
// the way getting packet size should be decided by user too.
// ---
// Example of GetPacketSize function
// when using first 4-bytes int of packet as entire packet size
/*
int GetPakcetSize(char* packet)
{
	int size = *BytesToType<int>(packet);
	return size;
}
*/

// Bit converter
template<typename T>
T* BytesToType(char* const pBytes, const int index = 0)
{
	return reinterpret_cast<T*>(pBytes + index);
}

template<typename T>
char* TypeToBytes(T* const pData)
{
	return reinterpret_cast<char*>(pData);
}