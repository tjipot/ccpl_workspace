/*
 * @UNIVESRE.COM @Nov 25,2016 @HYE
 * This program is the udp version of sending a file, which uses socket of SOCK_DGRAM
 * (udp) protocal. After each udp sending, there will be an usleep(20) pause of main 
 * process, ensuring the packet to arrive to recver sequentially. It is designed like 
 * this for the reason the execution of the process is much much much faster than that 
 * of sending a packet. 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define FILE_NAME_LEN 1024

typedef struct{
	char filename[FILE_NAME_LEN];
	long filelen;
}structFileInfo_t;

void err(const char * msg){
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char *argv[]){

	if(argc != 4){
		err("Command Format: \"./udp_file_send ip_address port_number filename\"");
	}

	int n;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		err("Sockfd Error, Quit.");
	}

	structFileInfo_t fileinfo;
	bzero(&fileinfo, sizeof(fileinfo));

	int fd = open(argv[3], O_RDONLY);
	if(fd < 0){
		err("Open File Error, Quit.");
	}
	strcpy(fileinfo.filename, argv[3]);
	fileinfo.filelen = lseek(fd, 0, SEEK_END);
	printf("File Size: %ld\n", fileinfo.filelen);

	//Recver's Addr Structure;
	struct sockaddr_in recvaddr;
	bzero(&recvaddr, sizeof(recvaddr));
	recvaddr.sin_family = AF_INET;
	recvaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[2], &recvaddr.sin_addr);

	//Send File Info Firstly;
	n = sendto(sockfd, &fileinfo, sizeof(fileinfo), 0, (struct sockaddr*)&recvaddr, sizeof(recvaddr));
	if(n != sizeof(fileinfo)){
		err("Send File Info Error, Quit.");
	}

	//After Sending File Info, the file should be sent;
	lseek(fd, 0, SEEK_SET);
	char send_buffer[1024] = {0};
	int count = 0;
	while((n = read(fd, send_buffer, 1024)) != 0){
		count = count + n;
		sendto(sockfd, send_buffer, n, 0, (struct sockaddr*)&recvaddr, sizeof(recvaddr));
		usleep(20);
	}
	printf("Send %d bytes.\n", count);
	close(fd);
	close(sockfd);

	return 0;
}