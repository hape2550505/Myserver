概述
---------------
* 项目描述：Linux下实现的高性能web服务器
* 设计与实现：

1. 使用线程池避免线程反复创建销毁的开销
2. 使用模拟Proactor+epoll+边缘触发(ET) 实现高并发处理请求。
3. 使用EPOLLONESHOT保证一个socket连接在任意时刻都只被一个线程处理。
4. 使用状态机解析HTTP请求报文，支持GET/POST请求，支持长连接
5. 使用priority queue实现的最小堆结构管理定时器，实现对超时长连接的处理。
6. 实现异步日志系统，记录服务器运行状态。
7. 封装互斥器，条件变量，信号量等线程同步互斥机制。
8. 使用shared_ptr管理指针，防止内存泄漏。
9. Webbench压力测试可以实现上万的并发连接数据交换，60M宽带下QPS为6k

基础测试
------------
* make server
* ./server port 启动服务器
* 浏览器端输入 ip:port 访问页面

![QQ截图20210301231726](https://github.com/hape2550505/Myserver/tree/master/image/QQ截图20210301231726.png)

![QQ截图20210301231837](https://github.com/hape2550505/Myserver/tree/master/image/QQ截图20210301231837.png)

## 压力测试

60M宽带 4核2.5GHz 4G内存 测试为6kQPS（主要受网速限制）![image-20210115100525443](https://github.com/hape2550505/Myserver/tree/master/image/image-20210115100525443.png)
