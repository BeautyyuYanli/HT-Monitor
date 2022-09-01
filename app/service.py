#  === TCP 服务端程序 server.py ===
# 导入socket 库（*表示导入所有可用函数和名字）
from socket import *
from unittest import result
import requests
app_token = 'ABCDEFG'   # 本处改成自己的应用 APP_TOKEN

# 变量名字大写通常表示配置项
# [socket编程常用的配置项：IP地址、端口号、缓冲区长度(BufferLength）]
# 主机地址为空字符串，表示本机所有可用的ip地址
# 客户端和服务端在同一台机器上，可用‘0.0.0.0’(不清楚IP地址)或‘127.0.0.1’（本机环回地址）
# 等待客户端来连接
IP = '192.168.1.101'
# 端口号
PORT = 50002
# 定义一次从socket缓冲区最多读入512个字节数据
BUFLEN = 512
# 温湿度合法界限
TEMP_MAX = 35
TEMP_MIN = 25
HUMI_MAX = 80
HUMI_MIN = 30


# 利用 wxpusher 的 web api 发送 json 数据包，实现微信信息的发送
def wxpusher_send_by_webapi(msg):
    webapi = 'http://wxpusher.zjiecode.com/api/send/message'
    data = {
        "appToken": app_token,
        "content": msg,
        "summary": msg[:99],  # 该参数可选，默认为 msg 的前10个字符
        "contentType": 1,
        "topicIds": [7120],
    }
    result = requests.post(url=webapi, json=data)
    return result.text


# 检查温湿度数据是否正常
def HT_value_vaild(s: str):
    s = s.split('\n')[1]
    t, h = [float(i) for i in s.split(',')]
    t = round(t / 1000, 1)
    h = h / 10
    if (t > TEMP_MAX or t < TEMP_MIN) or (h > HUMI_MAX or h < HUMI_MIN):
        return False, t, h
    else:
        return True, t, h


# 生成微信推送的消息内容
def wx_msg(t, h):
    s = '''
⚠⚠⚠警告⚠⚠⚠
检测到温湿度数据异常
温度：{}°C
湿度：{}%
'''.format(t, h)
    return s


if __name__ == "__main__":

    # socket是库中的一个类，有两个初始化参数(分别指明这个socket所用的传输层和网络层协议)
    # 类后加括号实例化一个socket对象，赋给监听socket(因为这是一个服务端程序，要等待客户端的连接)
    # 参数 AF_INET （internet）表示该socket网络层使用IP协议
    # 参数 SOCK_STREAM （一种流）表示该socket传输层使用tcp协议
    listenSocket = socket(AF_INET, SOCK_STREAM)

    # 调用socket类的bind()函数,绑定ip地址和端口,即与服务器连接的ip地址和端口号
    # 参数是（IP地址，端口号）二元组
    listenSocket.bind((IP, PORT))
    # 调用socket类的listen()函数，使socket处于监听状态，等待客户端的连接请求
    # 参数 8 表示 最多接受多少个等待连接的客户端（类似在排队的人数）
    listenSocket.listen(8)
    print(f'服务端启动成功，在{PORT}端口等待客户端连接...')

    # 此时，如果有客户端发来连接请求，就调用accept()函数连接客户端
    # 若没有连接请求，服务端程序在此处于阻塞（睡眠）状态

    # accept()函数有两个返回值：
    # 一个是一个新的socket对象，一个是连接它的客户端的地址（包括IP地址和端口号）
    # 可以将地址打印出来
    dataSocket, addr = listenSocket.accept()
    print('接受一个客户端连接:', addr)

    # while循环的作用：不断接收客户端发来的消息
    while True:
        # 调用数据socket的recv()方法，recieve(接收)，
        # 参数BUFLEN 指定从接收缓冲里最多读取多少字节
        # 这里的recvd接受的是字节串（bytes类型），与字符串（string类型）不同，网络传输用的都是字节串
        recved = dataSocket.recv(BUFLEN)

        # 读取的字节数据是bytes类型，需要调用bytes对象的decode()方法解码为字符串
        # 也有可能是音频数据、图像数据...有不同解码方式
        info = recved.decode()

        valid, t, h = HT_value_vaild(info)
        if not valid:
            result1 = wxpusher_send_by_webapi(wx_msg(t, h))
            print(result1)

        with open('data.txt', 'w') as f:
            f.write("{},{}".format(t, h))
