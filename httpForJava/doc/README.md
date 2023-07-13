# spider-http

爬虫相关起接口

此项目是在unidbg的基础上起的接口服务

- src/unidbg/myme是springboot起的接口
- src\unidbg\unidbg-android\src\main\java\com\kanxue\algorithmbase\MainActivity.java是APP相关的代码

如果你要修改代码打包方法如下

```
maven插件中:
  unidbg->clean->install
  myme->clean->package
```

### 运行

- 把myme下的myme.jar
- application.yml
- 需要运行的apk

放到同一文件夹下

```
java -jar myme.jar &
```

```
application.yml

spring:
  application:
    name: myme
server:
  port: 8080
apk:
  url: C:\Users\root\Desktop\test\algorithmbase_60.apk
```

### 测试

```
import os
import time
import random
import multiprocessing
from concurrent import futures

import requests

def foo(input_str):
    url="http://127.0.0.1:8080/web/getTest?input="+input_str
    res = requests.get(url=url,headers={
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
        "Accept-Encoding": "gzip, deflate, br",
        "Accept-Language": "zh-CN,zh;q=0.9",
        "Cache-Control": "no-cache",
        "Connection": "Close",
        "Host": "127.0.0.1:8080",
        "Pragma": "no-cache",
        "Upgrade-Insecure-Requests": "1",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36",
    })
    
    return (time.time(),res.text,os.getpid())


if __name__ == '__main__':
    s="ZKj9nyf0wDVX1s5YbdxSoILaUpPBCHg8uvNO4klm6iJGhQ7eFrWczAMEq3RTt2"
    input_list= [s[:random.randint(0,len(s)-1)] for _ in range(1000)]
    
    start_time = time.time();
    # foo(s)
    ex = futures.ProcessPoolExecutor(max_workers=24)
    results = ex.map(foo,input_list)
    for item in results:
        print("1",item)
    end_time=time.time()
    
    start_time2 = time.time();
    for item2 in input_list:
        print("2",foo(item2))
        
    print("time",end_time-start_time)
    print("time2",time.time()-start_time2)
    """
    测试: 6核8代i7
    0.3010838031768799 * 1000 301
    time 76.5913233757019
    time2 252.8527250289917
    """
```





