#include <stdio.h>

int main(void){
	int a[6] = {11, 4, 2, 5, 6, 1};
	int tmp = 0;

	for(int i=0; i<6; i++){
		for(int j=0; j<6-i-1; j++){
			if(a[j] > a[j+1]){
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}

	for(int i=0; i<6; i++){
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}