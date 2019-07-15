#include "../lsbIOCP/IOCPServerNet.h"
#include "../lsbIOCP/Acceptor.h"

#include <sstream>

int main()
{
	const char* ip = "127.0.0.1";
	u_short port = 11011;

	std::stringstream ss;
	ss << "hi" << '-' << 1;
	printf("%s", ss.str().c_str());

	/*Acceptor server(ip, port);

	server.Start();

	server.Join();*/

	return 0;
}