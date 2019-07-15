#include "AIOException.h"

std::string FormatErrorMessage(DWORD error, const std::string& msg)
{
	static const int BUFFERLENGTH = 1024;
	std::vector<char> buf(BUFFERLENGTH);
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf.data(), BUFFERLENGTH - 1, 0);
	return std::string(buf.data()) + " (" + msg + ")";
}

void ThrowLastErrorIf(bool expression, const std::string& msg)
{
	if (expression) {
		throw AIOException(GetLastError(), msg);
	}
}