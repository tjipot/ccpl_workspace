#include <stdio.h>
/*
 * SimpleSort.c
 *
 *  Created on: 2016年10月20日
 *      Author: haoranye
 */

int main(void){

	int array[8] = {3, 516, 43, 67, 734, 21, 12, 75};
	int tmp;

	//i = 8在这里不要紧, 因为下面就算j=i+1, 也有限制条件j<8去约束的;
	for(int i = 0; i < 8; i++){
		for(int j = i+1; j < 8; j++){
			if(array[i] > array[j]){
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}

	for(int i = 0; i < 8; i++){
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
