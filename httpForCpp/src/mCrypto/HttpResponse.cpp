#include "HttpResponse.h"
#include "Md5.h"
#include <string>
#include <regex>

using namespace std;

HttpResponse::HttpResponse()
{
}

HttpResponse::~HttpResponse()
{
}

bool HttpResponse::setRequest(std::string request)
{
	string src = request;
	string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
	regex r(pattern);
	smatch mas;
	regex_search(src, mas, r);
	if (mas.size() == 0)
	{
		printf("Filed to Regex %s\r\n", pattern.c_str());
		return false;
	}
	string type = mas[1];
	string path = "/";
	path += mas[2];
	string filetype = mas[3];
	string query = mas[4];
	if (type != "GET")
	{
		printf("Filed to Mode GET\r\n");
		return false;
	}
	string filename = path;
	if (path == "/")
	{
		filename = "/index.html";
	}

	string filepath = "www";
	filepath += filename;
	// php-cgi www/index.php crypto=abcd >  www/index.php.html
	// http://192.168.1.118:8888/index.php?crypto=Wangshdsdjdjask
	if (filetype == ".php")
	{
		string cryptoStr = query.substr(7);
		MD5 md5;
		md5.update("ollvm_md5");
		md5.update(cryptoStr);
		
		string cmd = "php-cgi ";
		cmd += filepath;
		cmd += " ";
		//for (int i = 0; i < query.size(); i++)
		//{
		//	if (query[i] == '&') query[i] = ' ';
		//}
		cmd += query;
		cmd += " md5=";
		cmd += md5.toString();
		cmd += " > ";
		filepath += ".html";
		cmd += filepath;
		//printf("%s\n", cmd.c_str());
		system(cmd.c_str());

	}


	fp = fopen(filepath.c_str(), "rb");
	if (fp == NULL)
	{
		printf("Failed to open file %s\r\n", filepath.c_str());
		return false;
	}
	//获取文件大小
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, 0);
	//printf("file size is %d\n",filesize);

	if (filetype == ".php")
	{
		char c = 0;
		int headsize = 0;
		while (fread(&c, 1, 1, fp) > 0)
		{
			headsize++;
			if (c == '8')
			{
				fseek(fp, 3, SEEK_CUR);
				headsize += 3;
				break;
			}
		}
		filesize = filesize - headsize;
	}

	return true;
}

std::string HttpResponse::getHead()
{
	string rmsg = "";
	rmsg = "HTTP/1.1 200 OK\r\n";
	rmsg += "Server: Myme\r\n";
	rmsg += "Content-Type: text/html\r\n";
	rmsg += "Content-Length: ";
	char bsize[128] = { 0 };
	sprintf(bsize, "%d", filesize);
	rmsg += bsize;
	rmsg += "\r\n\r\n";
	return rmsg;
}

int HttpResponse::read(char* buf, int bufsize)
{
	return fread(buf, 1, bufsize, fp);
}
