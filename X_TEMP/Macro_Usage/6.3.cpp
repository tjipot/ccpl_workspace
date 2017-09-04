#include <stdio.h>
#define MIN(a, b) a<b?a:b
#define MIN1(a, b) a<b?a:b;

int main(void){

	int tmp = MIN(1, 2);
	printf("The Smaller: %d.\n", tmp);

	int tmp1 = MIN1(1, 2) printf("MORE..\n");
	printf("The Smaller1: %d.\n", tmp1);

	return 0;
}
