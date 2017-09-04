// @1210OCT26,2016, 整形指针, 普通整数变量注意点:
// 整形指针是指针, 只能做地址相关的操作, 而不能当做普通整数变量一样进行整数值的操作;
#include <stdio.h>

int main(){
	int value1 = 2;
	int *tmp1 ;
	int *tmp2 ;
	int *tmp3 = NULL;
	// tmp1 = &value1;
	// *tmp2 = 2;
	*tmp3 = 2; //整数指针只能当做指针来用, 而不能当一个普通整形变量来用, 这行代码是个Segament fault 11错误;
	// *tmp3;
	// printf("%p, %p, %d.\n", tmp1, tmp2, *tmp3);
	tmp2 = tmp1;
	// tmp3 = &value1;
	// *tmp3 = value1;
	// printf("%p, %p, %d.\n", tmp1, tmp2, *tmp3);
	// printf("%p, %p, %p.\n", tmp1, tmp2, tmp3);
	// 172-26-114-119:desktop haoranye$ ./test
	// 0x7fff535b3b88, 0x0, 0x0.
	// Segmentation fault: 11



	return 0;
}