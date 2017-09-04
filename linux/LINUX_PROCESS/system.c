#include "common.h"
//#include <stdlib.h>

int main(void){

	printf("Running ps With system().\n");
	system("ps &");
	printf("Done.\n");

	return 0;
}