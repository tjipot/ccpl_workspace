/*
 * @UNIVESRE.COM @Nov 17, 2016 @HYE
 * Demonstrates the sending of a file("leaf.mp3") under TCP protocal, will be working
 * with the receiver: "FileRecver.c". The receiver's IP(e.g 127.0.0.1) and file's 
 * filename are required as the arguments of the program in the terminal window.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define PORT 9999
#define NAMELEN 1024
/* 说明: With File Name */
typedef struct{
	char filename[NAMELEN];
	long filelen;
}struFileInfo_t;


void err_sys(const char* msg){
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char *argv[]){
	if(argc != 3)
		err_sys("Usage:./FileSender receiver_IP filename");
	
	int ret;
	//创建套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("Socket Error");

	// err_sys("Test Msg");

	//定义地址结构，用于connect操作
	struct sockaddr_in dstaddr;
	bzero(&dstaddr, sizeof(dstaddr));
	dstaddr.sin_family = AF_INET;
	dstaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, argv[1], &dstaddr.sin_addr);

	//发起连接
	ret = connect(sockfd, (struct sockaddr*)&dstaddr, sizeof(dstaddr));
	if(ret < 0)
		err_sys("Connect Error..");
	printf("Connect Success.\n");
	
	//打开文件
	int fd = -1;
	fd = open(argv[2], O_RDONLY);
	if(fd < 0)
		err_sys("Open Error");
	
	//发送文件信息
	struFileInfo_t info;
	bzero(&info, sizeof(info));
	strncpy(info.filename, argv[2], strlen(argv[2]));
	info.filelen = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	printf("File Name:%s, File Length:%ld\n", info.filename, info.filelen);
	if(write(sockfd, &info, sizeof(info)) != sizeof(info)){//这句和recv中的相对应的那句都不能少;
		err_sys("write Error");
	}

	//循环读取并发送
	while(1){
		int n;
		char buffer[4096] = {0};
		n = read(fd, buffer, 4096);
		if(n < 0){
			err_sys("Read Error");
		}else if(n > 0){
			write(sockfd, buffer, n);
		}else{ //n == 0，读到文件结尾
			close(fd);
			break;
		}
	}
	close(sockfd);
	printf("File Send Finished.\n");
	
	return 0;
}


















