/*
 * @UNIVESRE.COM @Nov 24,2016 @HYE
 * Description: this program is the server side of a tcp connection which uses select()
 * as a way of I/O reuse;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#define PORT 9999

void err(const char * msg){ //Helper function
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char *argv[]){
	if(argc != 3)
		err("Usage:./tcp_select_server ipaddr port");
	
	int ret;

	//创建套接字
	int servfd = socket(AF_INET, SOCK_STREAM, 0); 
	if(servfd < 0)
		err("Socket error");

	//定义地址结构，用于bind操作
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2])); // ascii to integer
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // pointer addr to network addr;

	//绑定套接字
	ret = bind(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret < 0)
		err("Bind error");

	//将套接字改为监听套接字, 操作系统会设置一个连接队列, 记录所有向该套接字发起连接的请求, 之后accept;
	ret = listen(servfd, 5);
	if(ret < 0)
		err("Listen error.");
	printf("Server listening..\n");

	//等待客户端连接
	while(1){ //第一个while用于不停accept客户端的连接(通过listen()加入进来)
		// 创建客户端的套接字地址结构;
		struct sockaddr_in cliaddr;
		socklen_t addrlen;
		int clifd;//客户端套接字
		addrlen = sizeof(cliaddr);

		//服务端接收一个连接, 与客户端的connect对应, 成功返回后, 连接建立;
		clifd = accept(servfd, (struct sockaddr*)&cliaddr, &addrlen); //在这里, 只能等前一个clifd输入"stop"之后, 退出了第二层的while循环后, 这个accept才会被执行到, 继而接受一个已在listen但还没有被accept的连接;
		
		char ip[16] = {0}; //两个地方是要转换的: 1.地址格式: 点分十进制->网络格式, 2.端口号: 网络大端<->本地小端
		printf("Client addr:%s ", inet_ntop(AF_INET, &cliaddr.sin_addr, ip, 16));
		printf("Port:%d\n", ntohs(cliaddr.sin_port));

		//开始收发数据;
		while(1){
			fd_set read_set;//定义fd读集, 每次while循环进来都创建一个新的read_set, 但这不影响;
			FD_ZERO(&read_set);//清空;
			FD_SET(0, &read_set);//加入标准输入
			FD_SET(clifd, &read_set);//加入套接字
			struct timeval tv = {5, 0};
			
			//永远等直到指定的描述符可读
			//ret = select(clifd + 1, &read_set, NULL, NULL, NULL);
			ret = select(clifd + 1, &read_set, NULL, NULL, &tv); //把读集加入;
			if(ret == 0) //超时
				continue;
			
			//逐个检测描述符，并读取数据, 下面是标准输入fd(0为读); 这里的标准输入是对于此服务端来说的, 这里只能处理server端的输入和一个clifd的输入, 要是;
			if(FD_ISSET(0, &read_set)){ //标准输入可读
				char input[1024] = {0};
				scanf("%s", input);//阻塞, 然而有了select, 从clifd的读取不会阻塞;
				if(strncmp(input, "stop", strlen("stop")) == 0){
					close(clifd);//服务发起主动关闭
					break;
				}
				
				fd_set write_set;
				FD_ZERO(&write_set);
				FD_SET(clifd, &write_set);
				select(clifd + 1, NULL, &write_set, NULL, NULL);
				if(FD_ISSET(clifd, &write_set)){//如果套接字可写
					send(clifd, input, strlen(input), 0);
				}
				//printf("%s\n", input);
			}
			//下面是clifd;
			if(FD_ISSET(clifd, &read_set)){ //套接字可读
				char buffer[1024] = {0};
				int n;
				//等待接受数据
				n = recv(clifd, buffer, 1024, 0);
				if(n < 0)
					err("Recv error");
				else if(n == 0){//客户端主动关闭连接
					printf("Client closed.\n");
					close(clifd);
					break;
				}else{
					buffer[n] = '\0';
					printf("Serv recv:%s\n", buffer);
				}	
			}
		}
	}
	return 0;
}
