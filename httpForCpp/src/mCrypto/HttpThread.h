#pragma once
#include "MyTcp.h"
#include "HttpResponse.h"

class HttpThread {
public:
	MyTcp client;
	HttpResponse res;
	HttpThread();
	~HttpThread();
	bool start(MyTcp client);
	void Main();
};