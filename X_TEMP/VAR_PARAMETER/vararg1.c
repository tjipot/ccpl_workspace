#include <stdio.h>
/*
	@OCT22, 2016
	@Variable Arguments
*/

void print(int n, ...){

	int *p, i;
	p = &n + 1;
	for(i = 0; i < n; i++){
		printf("%p ", p+i);
		printf("%d ", *(p+i));
	}
	printf("\n");
	return;
}

int main(void){

	print(5, 1, 2, 3, 4, 5);

	return 0;
}
