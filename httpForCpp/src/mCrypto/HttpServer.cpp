#include "HttpServer.h"
#include "HttpThread.h"

#include <thread>

HttpServer::HttpServer()
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::Main()
{
	while (!isExit)
	{
		MyTcp client = server.maccept();
		if (client.sock <= 0)continue;
		HttpThread* th = new HttpThread();
		th->start(client);
	}
}

bool HttpServer::start(unsigned short port)
{
	isExit = false;
	server.createSocket();
	if (!server.mbind(port)) {
		return false;
	}
	std::thread sth(&HttpServer::Main, this);
	sth.detach();
	return true;
}

void HttpServer::stop()
{
	isExit = true;
}
