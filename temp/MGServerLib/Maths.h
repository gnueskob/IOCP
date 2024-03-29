#pragma once

#include <Windows.h>
#include <deque>

// TODO:사용 할 시 cuncurrent_queue 멀티 쓰레드에 safe한 큐 -> 
// 초기부터 사용할 unique index를 미리 할당해놓고 필요할 때마다 사용, 반환
class ULONG_PTRGenerator
{
public:
	typedef std::deque<ULONG_PTR>			tREUSELIST;
	typedef std::deque<ULONG_PTR>::iterator	tREUSELISTITER;
	static const ULONG_PTR cDefaultStart = 0;
	static const ULONG_PTR cMinMultiple = 1;
	static const ULONG_PTR cMaxMultiple = 10000;


public:
	ULONG_PTRGenerator(ULONG_PTR start=cDefaultStart, 
						ULONG_PTR multiple=cMinMultiple) : 
														reuseList(), 
														currentNumber(start), 
														multiple(multiple)
	{
		if (cMinMultiple > multiple || cMaxMultiple < multiple) {
			throw "multiple error";
		}
	}

	virtual ~ULONG_PTRGenerator()
	{
		reset();
	}

	void reset(ULONG_PTR start=cDefaultStart)
	{
		reuseList.clear();
		currentNumber = start;
	}

	ULONG_PTR retrieve()
	{
		if(reuseList.empty())
		{
			currentNumber += multiple;
			return currentNumber;
		}

		ULONG_PTR n = reuseList.front();
		reuseList.erase(reuseList.begin());
		return n;
	}

	bool release(ULONG_PTR n, bool bValid=false)
	{
		if(bValid)
		{
			for(auto iter = reuseList.begin() ; iter != reuseList.end() ; ++iter )
			{
				if (n == *iter) {
					return false;
				}
			}			
		}

		reuseList.push_back(n);
		return true;
	}


private:
	tREUSELIST		reuseList;
	ULONG_PTR		multiple;
	ULONG_PTR		currentNumber;
};

class UniqueIntegerGenerator
{
public:
	typedef std::deque<int>			tREUSELIST;
	typedef std::deque<int>::iterator	tREUSELISTITER;
	static const int cDefaultStart = 0;
	static const int cMinMultiple = 1;
	static const int cMaxMultiple = 10000;

public:
	UniqueIntegerGenerator(int start=cDefaultStart, 
							int multiple=cMinMultiple) : reuseList(), 
														currentNumber(start), 
														multiple(multiple)
	{
		if (cMinMultiple > multiple || cMaxMultiple < multiple) {
			throw "multiple error";
		}
	}

	virtual ~UniqueIntegerGenerator()
	{
		reset();
	}

	void reset(int start=cDefaultStart)
	{
		reuseList.clear();
		currentNumber = start;
	}

	int retrieve()
	{
		if(reuseList.empty())
		{
			currentNumber += multiple;
			return currentNumber;
		}

		int n = reuseList.front();
		reuseList.erase(reuseList.begin());
		return n;
	}

	bool release(int n, bool bValid=false)
	{
		if(bValid)
		{
			for( auto iter = reuseList.begin() ; iter != reuseList.end() ; ++iter )
			{
				if (n == *iter) {
					return false;
				}
			}			
		}

		reuseList.push_back(n);
		return true;
	}


private:
	tREUSELIST		reuseList;
	int		multiple;
	int		currentNumber;
};

//class RandomGenerator
//{
//	unsigned int		w;
//	unsigned int		z;
//public:
//
//	RandomGenerator(unsigned int sw, unsigned int sz) : w(sw), z(sz)
//	{
//	}
//
//	~RandomGenerator()
//	{
//	}
//
//	unsigned int Get()
//	{
//		z = 36969 * (z & 65535) + (z >> 16);
//		w = 18000 * (w & 65535) + (w >> 16);
//		return (z << 16) + w;
//	}
//
//};

