#include "HttpThread.h"
#include <thread>

HttpThread::HttpThread()
{
}

HttpThread::~HttpThread()
{
}

bool HttpThread::start(MyTcp client)
{
	this->client = client;
	std::thread sth(&HttpThread::Main, this);
	sth.detach();
	return true;
}

void HttpThread::Main()
{
	char buf[10240] = { 0 };
	for (;;) {
		int len = client.mrecv(buf, sizeof(buf) - 1);
		if (len <= 0)break;
		buf[len] = '\0';
		if (!res.setRequest(buf))break;
		std::string head = res.getHead();
		if (client.msend(head.c_str(), head.size()) <= 0)break;
		int size = sizeof(buf);
		bool error = false;
		for (;;) {
			int length = res.read(buf, size);
			if (length < 0) {
				error = true;
				break;
			}
			if (length == 0)break;
			if (client.msend(buf, length) <= 0) {
				error = true;
				break;
			}
		}
	}
	client.mclose();
	delete this;
}
