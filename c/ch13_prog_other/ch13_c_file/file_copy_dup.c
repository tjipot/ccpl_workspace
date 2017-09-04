/*
 * @UNIVESRE.COM @Nov 22, 2016 @HYE
 * Demonstrates the copy from one file to another created file, as well as the
 * demo of file descriptor's duplication used in file write. The source file is
 * "flying_bird_and_fish.txt", which was written by Tagore.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void){

 	int n = 0, count = 0;
 	int sourceFileFd = -1, newFileFd = -1, dupFd = -1;
 	char buffer[1024] = {0};
 	// memset(buffer, '\0', sizeof(buffer));

 	sourceFileFd = open("flying_bird_and_fish.txt", O_RDWR);
 	newFileFd = open("flying_bird_and_fish_dup.txt", O_RDWR | O_CREAT, 0755);

 	if(sourceFileFd < 0){
 		printf("sourceFileFd Failure. Exit.\n");
 		exit(-1);
 	}else{
 		printf("sourceFileFd is %d\n", sourceFileFd);
 	}

 	if(newFileFd < 0){
 		printf("newFileFd Failure.\n");
 		exit(-1);
 	}else{
 		printf("newFileFd is %d.\n", newFileFd);
 		dupFd = dup(newFileFd);
 		printf("dupFd is %d.\n", dupFd);
 	}

 	n = read(sourceFileFd, buffer, 1024);
 	while(n > 0){
 		// printf("Read %d bytes.\n", n);
 		printf("%s", buffer); // 不能读1024个bytes进来, 否则buffer最后一个byte会是乱码;
 		// 感觉, 乱码出现的原因是printf会在一个buffer数组输出完之后继续往后读一个或几个byte直到遇到了'\0'(如果在buffer数组中添加了'\0'终止标记的话, printf就结束, 不会有乱码; 乱码是printf照着buffer的地址开始输出, 直到输出完1024bytes后还没遇到\'0', 继续输出, 最后终于遇到了'\0')

 		// printf("Size: %lu, H%cH\n", sizeof(buffer), buffer[1023]);
 		write(newFileFd, "\n****\n", strlen("\n****\n"));
 		int i = write(dupFd, buffer, n);
 		// strncpy(newFileFd, buffer, n);
 		// printf("Writen %d bytes.\n", i);
 		// *buffer = 0;
 		// strncpy(buffer, "", strlen(""));
 		memset(buffer, '\0', sizeof(buffer));
 		n = read(sourceFileFd, buffer, 1024);
 	}
 	printf("\n");

 	close(sourceFileFd);
 	close(newFileFd);
 	close(dupFd);

 	return 0;
 }