/* @UNIVESRE.COM_2052OCT212016_HYe
 * merge_sort.c */

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right){
	int l = left, r = mid + 1, k = 0;
	int* tmp = (int*)malloc(sizeof(int) * (right - left + 1));
	while(l <= mid && r <= right){
		if(arr[l] < arr[r]){
			tmp[k] = arr[l]; k++; l++;
		}else{
			tmp[k] = arr[r]; k++; r++;
		}
	}
	if(l <= mid){
		while(l <= mid){
			tmp[k] = arr[l]; k++; l++;
		}
	}
	if(r <= right){
		while(r <= right){
			tmp[k] = arr[r]; k++; r++;
		}
	}
	
	for(k = 0, l = left; l <= right; l++){
		arr[l] = tmp[k];
		k++;
	}
	free(tmp);
	return;
}

void mergeSort(int arr[],int left,int right){
	int mid = 0;
	if(left < right){
		mid = (left + right)/2; //一层一层把index打散掉; 在打这句话的时候, enter键奇迹般的又好回来了, 我只是习惯性错误地去按了一下, @18:14, OCT21, 2016, 火车上;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}else{
		return;
	}
}

int main(void){

	int arr[10] = {1, 23, 54, 39, 28, 84, 73, 74, 50, 93};
	mergeSort(arr, 0, 9);
	for(int i = 0; i <= 9; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
