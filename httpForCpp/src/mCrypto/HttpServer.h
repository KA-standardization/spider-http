#pragma once
#include "MyTcp.h"

class HttpServer
{
public:
	bool isExit = false;
	HttpServer();
	~HttpServer();
	MyTcp server;
	void Main();
	bool start(unsigned short port);
	void stop();
};
