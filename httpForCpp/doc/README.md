# spider-httpForCPP

>解决一些魔改算法或汇编还原算法起接口的问题
>
>http://192.168.1.118:8888/index.php?crypto=Wangshdsdjdjask

#### 环境

> yum install php-cgi

#### 资源

> 资源文件放在src\www\下

#### 通信

> 通信用的socket，文件在src\mySocketDll\下

```
makefile
libmySocketDll.so:MyTcp.cpp MyTcp.h
	g++ $+ -o ../../lib/$@ -fpic -shared -std=c++11
```

#### 逻辑

> 主代码放在src\mCrypto\下
>
> 这个里例子是魔改的MD5算法
>
> 用在你的项目时，你需要更改
>
> - makefile: 把Md5.cpp替换为你自己的文件
> - HttpResponse.cpp: 把Md5相关替换为你自己的逻辑
> - www/index.php: 根据自己的需求更改

```
makefile
server:server.cpp HttpResponse.cpp HttpServer.cpp HttpThread.cpp Md5.cpp
	g++ $+ -o ../../bin/$@ -I../mySocketDll -std=c++11 -lpthread -lmySocketDll -L../../lib
```

```
HttpResponse.cpp
#include "HttpResponse.h"
#include "Md5.h"
#include <string>
#include <regex>
bool HttpResponse::setRequest(std::string request)
...
		MD5 md5;
		md5.update("ollvm_md5");
		md5.update(cryptoStr);
		...
		cmd += query;
		cmd += " md5=";
		cmd += md5.toString();
...
```

```
index.php
<?php
	echo "crypto=".$_GET["crypto"];
	echo "&";
	echo "md5=".$_GET["md5"];
?>
```

