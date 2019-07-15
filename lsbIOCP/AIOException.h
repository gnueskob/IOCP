#pragma once

#include <windows.h>
#include <stdlib.h>

#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

std::string FormatErrorMessage(DWORD error, const std::string& msg);
void ThrowLastErrorIf(bool expression, const std::string& msg);

// windows 예외 처리
// https://docs.microsoft.com/ko-kr/cpp/cpp/how-to-interface-between-exceptional-and-non-exceptional-code?view=vs-2019
class AIOException : public std::runtime_error
{
private:
	DWORD m_error;

public:
	AIOException(DWORD error, const std::string& msg)
		: std::runtime_error(FormatErrorMessage(error, msg)), m_error(error) {}
	DWORD GetErrorCode() const { return m_error; }
};