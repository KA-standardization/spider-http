#include "MyTcp.h"
#ifdef WIN32
#include <windows.h>
#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#define closesocket close
#define strcpy_s strcpy
#endif // WIN32
#include <thread>
#include <stdio.h>
#include <string.h>

using namespace std;

MyTcp::MyTcp()
{
#ifdef WIN32
	static bool init = true;
	if (init) {
		init = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif //WIN32
}

MyTcp::~MyTcp()
{
}

int MyTcp::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Failed to Socket init\r\n");
	}
	return sock;
}

bool MyTcp::mbind(unsigned short port)
{
	if (sock <= 0) {
		createSocket();
	}
	sockaddr_in saddr;
	saddr.sin_addr.s_addr = htonl(0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		printf("Failed to bind, port->%d\r\n", port);
		return false;
	}
	printf("Success to bind, port->%d\r\n", port);
	listen(sock, 10);
	printf("Success to listen, socket->%d\r\n", sock);
	return true;
}

MyTcp MyTcp::maccept()
{
	MyTcp tcp;
	sockaddr_in caddr;
	socklen_t clen = sizeof(caddr);
	int client_sock = ::accept(sock, (sockaddr*)&caddr, &clen);
	if (client_sock <= 0) return tcp;
	printf("Success to accept, clientSock->%d\r\n", client_sock);
	char* ip = inet_ntoa(caddr.sin_addr);
	strcpy_s(tcp.ip, ip);
	tcp.port = ntohs(caddr.sin_port);
	tcp.sock = client_sock;
	printf("clientSock sock->%d, ip->%s, port->%d\r\n", client_sock, tcp.ip, tcp.port);
	return tcp;
}

bool MyTcp::mconnect(const char* ip, unsigned short port, int timeoutms)
{
	if (sock <= 0) createSocket();
	sockaddr_in saddr;
	saddr.sin_addr.s_addr = inet_addr(ip);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	fd_set set;
	if (connect(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		printf("setBlock false\r\n");
		FD_ZERO(&set);
		FD_SET(sock, &set);
		timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = timeoutms * 1000;
		if (select(sock + 1, 0, &set, 0, &tm) <= 0) {
			printf("Falied to connect\r\n %s:%d\r\n", ip, port);
			return false;
		}
	}
	setBlock(true);
	printf("Success to connect %s:%d\r\n", ip, port);
	return false;
}

bool MyTcp::setBlock(bool flag)
{
	if (sock <= 0) return false;
#ifdef WIN32
	// 0表示阻塞
	unsigned long ul = 0;
	// 1表示非阻塞
	if (!flag) ul = 1;
	ioctlsocket(sock, FIONBIO, &ul);
#else
	int flag_l = fcntl(sock, F_GETFL, 0);
	if (flag_l < 0)return false;
	if (flag) {
		flag_l = flag_l & ~O_NONBLOCK;
	}
	else
	{
		flag_l = flag_l | O_NONBLOCK;
	}
	// fcntl(sock, FSETFL, flag_l) != 0 
	if (fcntl(sock, F_SETFL, flag_l) != 0)return false;
		
#endif // WIN32

	return true;
}

int MyTcp::mrecv(char* buf, int bufsize)
{
	return ::recv(sock,buf,bufsize,0);
}

int MyTcp::msend(const char* buf, int sendsize)
{
	int sendLen = 0;
	while (sendLen!=sendsize)
	{
		int len = ::send(sock, buf + sendLen, sendsize - sendLen, 0);
		if (len <= 0)break;
		sendLen += len;
	}
	return sendLen;
}

void MyTcp::mclose()
{
	if (sock <= 0)return;
	::closesocket(sock);
}
