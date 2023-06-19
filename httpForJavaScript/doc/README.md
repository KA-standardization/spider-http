# spider-http

> 解决一些JS加密代码运行起接口的问题

#### 环境

> 安装node
>
> npm install express -g
>
> 根据你的用例安装，我这里是知乎的只用到一个jsdom
>
> - npm install jsdom -g

#### 运行

> node /spider-http/httpForJavaScript/bin/run

#### 测试

```
import requests

def test_encrypt(text):
        res = requests.post('http://192.168.1.101:10247/encrypt', data={'myme': text})
        encrypt_str = res.text
        return encrypt_str

print(test_encrypt("abcdef0123456789"))
```

