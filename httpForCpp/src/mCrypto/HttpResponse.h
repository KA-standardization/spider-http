#pragma once
#include <string>

class HttpResponse {
private:
	int filesize = 0;
	FILE* fp = NULL;
public:
	HttpResponse();
	~HttpResponse();
	bool setRequest(std::string request);
	std::string getHead();
	int read(char* buf, int bufsize);
};