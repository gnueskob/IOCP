#pragma once

#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

string FormatErrorMessage(DWORD error, const string& msg);
void ThrowLastErrorIf(bool expression, const string& msg);

// windows 예외 처리
// https://docs.microsoft.com/ko-kr/cpp/cpp/how-to-interface-between-exceptional-and-non-exceptional-code?view=vs-2019
class AIOException : public runtime_error
{
private:
	DWORD m_error;
public:
	AIOException(DWORD error, const string& msg)
		: runtime_error(FormatErrorMessage(error, msg)), m_error(error) {}

	DWORD GetErrorCode() const { return m_error; }
};

string FormatErrorMessage(DWORD error, const string& msg)
{
	static const int BUFFERLENGTH = 1024;
	vector<char> buf(BUFFERLENGTH);
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf.data(), BUFFERLENGTH - 1, 0);
	return string(buf.data()) + " (" + msg + ")";
}

void ThrowLastErrorIf(bool expression, const string& msg)
{
	if (expression) {
		throw AIOException(GetLastError(), msg);
	}
}