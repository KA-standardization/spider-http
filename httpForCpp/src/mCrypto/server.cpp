#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "HttpServer.h"

int main(int argc, char* argv[]) {
	signal(SIGPIPE, SIG_IGN);
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}
	HttpServer server;
	server.start(port);

	getchar();
	return 0;
}