#ifndef MYTCP_H
#define MYTCP_H

#ifdef WIN32
#ifdef MYSOCKETDLL_EXPORTS
#define MYSOCKETDLL_API __declspec(dllexport)
#else
#define MYSOCKETDLL_API __declspec(dllimport)
#endif
#else
#define MYSOCKETDLL_API
#endif


class MYSOCKETDLL_API MyTcp
{
public:
	int sock = 0;
	unsigned short port = 0;
	char ip[16];
	MyTcp();
	virtual ~MyTcp();
	int createSocket();
	bool mbind(unsigned short port);
	MyTcp maccept();
	bool mconnect(const char* ip,unsigned short port,int timeoutms=1000);
	bool setBlock(bool flag);
	int mrecv(char* buf, int bufsize);
	int msend(const char* buf, int sendsize);
	void mclose();
};

#endif
