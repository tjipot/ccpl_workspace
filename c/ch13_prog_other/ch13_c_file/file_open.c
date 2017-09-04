/*
 * @UNIVESRE.COM @Nov 23, 2016 @HYE
 * Demonstrates the open operation of a file, and the prints out to that file
 * when standard out is closed.
 */

#include <sys/stat.h>	//file status
#include <sys/types.h>
#include <fcntl.h>		//file control
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// In:0, Out:1, Error:2, file descriptors are managed by OS, and each process in Unix could has 1024 file descriptors at most;
#define STDIN  0
#define STDOUT 1
#define STDERR 2

int main(){

	// struct stat buf;
	// stat("/etc/hosts", &buf);
	// printf("/etc/hosts file size = %lld\n", buf.st_size);

	// Open File Test;
	close(STDOUT);	//Close Stdout;
	int fd = -1;
	fd = open("tmp.txt", O_RDWR);	//fopen等f开头的函数都是库函数, open才是Unix类系统的系统调用;
	if(fd == -1){
		printf("File Open Failed..\n");	// STDOUT is closed, this will write to "tmp.txt";
		fd = open("tmp.txt", O_RDWR | O_CREAT, 0755);
		if(fd == -1){
			printf("File Create Failed..\n");
			exit(-1);
		}
		printf("File Created: fd is %d\n", fd);	// fd is 1 since STDOUT is closed;
	}else{
		printf("File Opened, fd is %d\n", fd);
	}

	fflush(stdout); //The function fflush() forces a write of all buffered data for the given output or update stream via the stream's underlying write function.  The open status of the stream is unaffected.
	close(fd);

	return 0;
}