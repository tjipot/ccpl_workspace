/*
 * @UNIVESRE.COM @Nov 25,2016 @HYE
 * This program is the udp version of receiving file program, which uses socket of 
 * SOCK_DGRAM(udp) protocal. After each udp sending, there will be an usleep(20) 
 * pause of main process, ensuring the packet to arrive to recver sequentially. 
 * It is designed like this for the reason the execution of the process is much 
 * much much faster than that of sending a packet. 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define  FILE_NAME_LEN 1024

typedef struct{
	char filename[FILE_NAME_LEN];
	long filelen;
}structFileInfo_t;

void err(const char * msg){
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char *argv[]){

	if(argc != 3){
		err("Command Format: \"./udp_file_recv ip_address port_number\"");
	}

	//Precedure: socket, send, recv, close

	int ret;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		err("Socket Error, Quit.");
	}

	//有socket的类型, 还得有为之服务的地址空间, 要bind;
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &addr.sin_addr);
	ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)); //sockfd和sockaddr地址结构的绑定;
	if(ret < 0){
		err("Bind Error, Quit.");
	}

	//Udp不需要连接, 可以直接收发数据: 先接收文件信息;
	int n;
	structFileInfo_t fileInfo;
	n = recvfrom(sockfd, &fileInfo, sizeof(fileInfo), 0, NULL, NULL);
	if(n != sizeof(fileInfo)){
		err("Recv File Info Error, Quit.");
	}else{
		printf("Recved File Name: %s, Length: %ld.\n", fileInfo.filename, fileInfo.filelen);
	}

	//Create Temporarily File And Prepare To Recv.
	strcat(fileInfo.filename, "_bak");
	FILE *fp = fopen(fileInfo.filename, "w+");
	if(fp == NULL){
		err("Fopen Error, Quit.");
	}

	int size = fileInfo.filelen;
	while(size > 0){
		char buffer[1024] = {0};
		n = recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);
		if(n > 0){
			fwrite(buffer, 1, n, fp);
		}
		size = size - n; //Reduce the size by the length already recved;
	}

	//Finished Receiving File;
	fclose(fp);
	close(sockfd);

	return 0;
}


