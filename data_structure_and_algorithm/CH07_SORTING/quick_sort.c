/* @UNIVESRE.COM @11302016 @HYe
 * QUICKSORT:
 * 1.fun(): left should always smaller than right, 
 * 2.repeat fun() until left(new) index just larger than right(new) index;
 * Concept Ref: ruanyifeng.com ->
 * http://www.ruanyifeng.com/blog/2011/04/quicksort_in_javascript.html */

#include <stdio.h>
#include <stdlib.h>

/* Helper Function */
void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


/* Alg Reference: http://www.algolist.net/Algorithms/Sorting/Quicksort */
int quickSort(int array[], int left, int right){
	int i = left, j = right;				//Array indexes;
	int pivot = array[(left + right)/2];	//Pivot value;

	/* Partition */
	while(i <= j){
		while(array[i] < pivot){
			i++;
		}
		while(array[j] > pivot){
			j--;
		}
		if(i <= j){
			swap(&array[i], &array[j]);
			i++;
			j--;
		}
	}

	/* Recursion */
	if(left < j){
		quickSort(array, left, j);
	}
	if(i < right){
		quickSort(array, i, right);
	}

	return 0;
}


// Ref: http://blog.chinaunix.net/uid-24774106-id-2238633.html;
// Des: 晦涩难懂;
// int partition(int array[], int left, int right){
// 	int pivot  = array[right];
// 	int curpos = left;
// 	int j;
//
// 	for(j = left; j<right; j++){
// 		if(array[j] < pivot){
// 			swap(&array[j], &array[curpos]);
// 			curpos++;
// 		}
// 	}
//
// 	swap(&array[r], &array[curpos]);
// 	return curpos;
// }
//
// void quicksort(int array[], int left, int right){
// 	int interval;
// 	if(left <  right){
// 		interval = partition(array, left, right);
// 		quicksort(array, left, interval - 1);
// 		quicksort(array, interval + 1, right);
// 	}
// }


/* Test Quicksort */
int main(void){

	int number_count = 20;
	int *array = malloc(number_count * sizeof(int));
	if(array == NULL){
		printf("malloc failed, return.\n");
		return -1;
	}

	for(int i=0; i<number_count; i++){
		array[i] = rand()%1000;
		printf("array[%d]=%d\n", i, array[i]);
	}

	quickSort(array, 0, 19);
	for(int i=0; i<number_count; i++){
		printf("array[%d]=%d\n", i, array[i]);
	}

	return 0;
}