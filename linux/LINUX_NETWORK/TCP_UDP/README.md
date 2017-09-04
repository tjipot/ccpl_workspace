#Linux_Network_Programming


##0.Linux网络通信前的准备

Linux中用TCP/UDP协议来发送文件需做两点前期准备:

###字节序转换/地址格式转换:

* 字节序转换: 网络采用的是大端字节序, 而本地机是小端(尾端放低地址), 故需转换;

	```
	#include <arpa/inet.h>
	uint32_t htonl(uint32_t hostlong);  //host to net long;	uint16_t htons(uint16_t hostshort); //host to net short;
	uint32_t ntohl(uint32_t netlong);   //net to host long;
	uint16_t ntohs(uint16_t netshort);  //net to host short;
	```

* 地址格式转换: 点分十进制(便于人的阅读) <-> 32 bits 无符整地址(机器识别的格式);

	```
	#include <arpa/inet.h>
	int inet_pton(int af, const char * restrict src, void * restrict dst); //internet point to net, return 32 bits net address;
	const char * inet_ntop(int af, const void * restrict src, char * restrict dst, socklen_t size); //internet net to point, return address in point formation;
	```

###IPv4 sockaddr:

* 关于地址结构: 地址结构是用来保存通信信息的(如IPv4型的地址结构), 不同的地址结构都需要转换为通用的sockaddr类型, 参考如下:

	```
	#include <netinet/in.h>

	//通用地址结构: sockaddr;
	struct sockaddr{
		sa_family_t sa_family;			//2 bytes
		char		sa_data[14];		//14 bytes
	};

	//IPv4地址结构: sockaddr_in, 在bind()中需转换成通用地址结构(struct sockaddr);
	struct sockaddr_in{
		sa_family_t 	sin_family;		//2 bytes
		in_port_t		sin_port;		//2 bytes
		struct in_addr	sin_addr;		//4 bytes
		char			sin_zero[8];	//8 bytes
	};

	//struct in_addr of sockaddr_in;
	struct in_addr{
		in_addr_t s_addr; 				//4 bytes
	};
	```

	
	
	

##1.TCP通信
TCP是面向连接的, 可靠的传输层协议, 什么是面向连接?! 从概念理解上, 不能把可以收发数据的通信模式就称为一种连接, 要不, UDP也可以称为面向连接的了. 这里指的面向连接是两个通信对象在通信时会建立一种专门用于通信的过程的机制, 打个比方, 就如打卡一样要进行确认;

###TCP编程架构 
* TCP客户端: socket() --------> connect() -----------> write() -> read()  -> close(); //主动
* TCP服务端: socket() -> bind()->listen()->accept() -> read()  -> write() -> close(); //被动

###TCP客户端接口: connect(), send(), recv();

* connect()函数: initiate a connection on a socket; 返回值: 成功0/失败-1; 如果对端IP地址正确, 但是没开启服务进程, 则会有75秒的等待时间;
     
	```
	#include <sys/types.h>
	#include <sys/socket.h>
	int connect(int socket, const struct sockaddr *address, socklen_t address_len);
	```
* send()函数: Send(), sendto(), and sendmsg() are used to transmit a message to another socket.  Send() may be used only when the socket is in a connected state, while sendto() and sendmsg() may be used at any time; 返回值: 成功:已发送的字节数/失败:-1;

	```
    #include <sys/socket.h>
    ssize_t send(int socket, const void *buffer, size_t length, int flags);
    ssize_t sendmsg(int socket, const struct msghdr *message, int flags);
	ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr,
         socklen_t dest_len);
	```
* recv()函数: the recv() function is normally used only on a connected socket (see connect(2)) and is identical
to recvfrom() with a null pointer passed as its address argument.  As it is redundant, it may not be supported in future releases; The recvfrom() and recvmsg() system calls are used to receive messages from a socket, and may be used to receive data on a socket whether or not it is connection-oriented.

	```
    #include <sys/socket.h>
    ssize_t recv(int socket, void *buffer, size_t length, int flags);	//Standard C Library (libc, -lc)
    ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags,
         struct sockaddr *restrict address, socklen_t *restrict address_len);
    ssize_t recvmsg(int socket, struct msghdr *message, int flags);
    ``` 

###TCP服务端接口: bind(), listen(), accept(), close();

* bind()函数: 同UDP的bind();
* listen()函数: listen for connections on socket, 将socket由主动改为被动, 并告知操作系统为该套接字创建一个连接队列; "creation of socket-based connections requires several operations: First, a socket is created with socket(2).  Next, a willingness to accept incoming connections and a queue limit for incoming connections are specified with listen().  Finally, the connections are accepted with accept(2).  The listen() call applies only to sockets of type SOCK_STREAM or SOCK_SEQPACKET"; 返回值: 成功0/失败-1;

	```
    #include <sys/socket.h>
    int listen(int socket, int backlog);
	```
* accept()函数: ACCEPT a connection on a socket (from connection list); 返回值: 成功:非负的descriptor of accepted socket/失败:-1;

	```
    #include <sys/socket.h>
    int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
	```
* close()函数: delete a descriptor, 关闭一个已连接的套接字将导致另一端接收到长度为0的数据包(而客户端关闭套接字, 意味着客户主动断开连接: 关闭操作即意味着知识点4次挥手的到来); when a process exits, all associated file descriptors are freed, but since there is a limit on active descriptors per processes, the close() function call is useful when a large quantity of file descriptors are being handled.

	```
    #include <unistd.h>
    int close(int fildes);
    ```
    
###TCP三次/四次握手
TCP包的首部有6个标志bits用于标识该数据包的类型: SYN, FIN, ACK, RST, PSH, URG;

* 客户端发起SYN连接(三次握手): 客户:SYN(J) -> 服务:SYN(K),ACK(J+1) ----- > 客户:ACK(K+1);
* 客户端关闭FIN连接(四次握手): 客户:FIN(M) -> 服务:ACK(M+1)/服务:FIN(N) -> 客户:ACK(N+1);

除了上述客户端发起的正常关闭之外, TCP还有可能被异常关闭, 这时关闭端将发送一个复位报文RST而不是FIN来释放一个连接; 异常终止将丢弃任何待发数据并立即发送复位报文RST, RST的接收方会区分另一端执行的是异常关闭还是正常关闭, 这要通过程序指定; RST报文不会导致另一端产生任何响应, 另一端根本不进行确认, 并且收到RST一端也将终止该连接, 将通知应用层连接复位.

###TCP并发编程
* 多进程式并发
* 多线程式并发


##2.UDP通信
用UDP协议进行传输时只要知道目的地址和端口, 不需要点到点地建立连接, 就可以发送和接收: 故是一种无连接的协议;

<示例程序: udp\_file\_send.c>

###UDP编程架构
网络编程统一采用socket接口来作为对本机以外的另一台机器中的进程的标记, 就好像文件要有file descriptor一样, 它们只不过一个面向网络, 一个面向本地而已; 另外, 某个socket具体要采用什么网络协议, 需要用Linux中提供的具体函数进行绑定(即, socket绑定某种协议), 但socket并不等于某一特定协议, 不要谈到了socket就以为是某一种协议专属的东西; 可以用read/write/close等函数对某一socket descriptor进行操作.

* UDP客户端: socket() -> sendto() -> recvfrom() -> close();  //客户端无bind();
* UDP服务端: socket() -> bind() ---> recvfrom() -> sendto(); //服务端无close();

###UDP函数接口:

函数接口: socket(), bind(), sendto(), recvfrom();

* 关于socket(): "Socket() creates an endpoint for communication and returns a descriptor", 默认情况下, socket()创建的descriptor是用来主动发起服务的, 如果要用在服务端, 则需改为被动的;

* 关于bind(): "assigns a name to an unnamed socket.  When a socket is created with socket(2) it exists in a name space (address family) but has no name assigned.  Bind() requests that address be assigned to the socket".
	
	```
	#include <sys/socket.h>
	int socket(int domain, int type, int protocol);
	int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
	ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address, socklen_t *restrict address_len); //Standard C Library (libc, -lc)
	```

