#include <stdio.h>

int main(void){
	int a[6] = {11, 4, 2, 5, 6, 1};
	int minindex, tmp = 0;
	for(int i = 0; i<6; i++){
		minindex = i;
		for(int j=i+1; j<6; j++){
			if(a[j] < a[minindex]){
				minindex = j;
			}
		}
		if(minindex != i){
			tmp = a[i];
			a[i] = a[minindex];
			a[minindex] = tmp;
		}
	}
	for(int i=0; i<6; i++){
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}