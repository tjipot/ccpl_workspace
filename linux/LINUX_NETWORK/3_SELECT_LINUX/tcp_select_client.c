/*
 * @UNIVESRE.COM @Nov 24,2016 @HYE
 * Description: this program is the client side of a tcp connection which uses select()
 * as a way of I/O reuse;
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

void err(const char * msg){
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char *argv[]){
	if(argc != 3)
		err("Usage:./tcp_select_client ipaddr port");
	
	//创建套接字
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err("Socket error");

	//指定connect地址
	struct sockaddr_in dst_addr;
	bzero(&dst_addr, sizeof(dst_addr));
	dst_addr.sin_family = AF_INET;
	dst_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &dst_addr.sin_addr);

	//发起connect操作
	int ret;
	ret = connect(sockfd, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
	if(ret != 0)
		err("Connect error");

	//读写操作
	char send_buf[1024] = {0};
	char recv_buf[1024] = {0};
	
	int maxfd = sockfd + 1;
	fd_set read_set;
	FD_ZERO(&read_set);
	while(1){
		FD_SET(0, &read_set); //把标准输入加入读集;
		FD_SET(sockfd, &read_set); //把sockfd加入读集;
		select(maxfd, &read_set, NULL, NULL, NULL);//阻塞，通知系统检测fd是否可读;
		
		if(FD_ISSET(0, &read_set)){ //如果标准输入可读: 当用户键入了一串字符;
			fgets(send_buf, 1024, stdin); //发送
			if(strncmp(send_buf, "stop", strlen("stop")) == 0)
				break;
			send(sockfd, send_buf, strlen(send_buf), 0);
		}
		
		if(FD_ISSET(sockfd, &read_set)){ //如果server那边发过来了msg: 接收;
			int ret;
			ret = recv(sockfd, recv_buf, 1024, 0);
			if(ret == 0){//服务器端主动关闭
				printf("Server closes connection.\n");
				break;		
			}
			recv_buf[ret] = '\0';
			printf("Recv:%s\n", recv_buf);	
		}
	}

	close(sockfd);
	return 0;
}
