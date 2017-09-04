/* @UNIVESRE.COM_20161219_HYe
 * shell_sort.c */

#include <stdio.h>

void Shellsort(int A[], int N){
    int i, j, Increment;
    int tmp;

    for(Increment = N/2; Increment > 0; Increment /= 2){
        for(i = Increment; i < N; i++) {
            tmp = A[i];
            for(j = i; j >= Increment; j -= Increment) {
                if(tmp < A[j - Increment]) {
                    A[j] = A[j - Increment];
                }else{
                    break;
                }
            }
            A[j] = tmp;
        }
    }
}

int main(void){

    // codes to run..

    return 0;
}