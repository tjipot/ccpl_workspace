/* @UNIVESRE.COM_20161218_HYe
 * Insert Sort: 具体看代码注释. */

#include <stdio.h>

int main(void){
	int a[6] = {11, 4, 2, 5, 6, 1};
	int i, j, tmp = 0;

	for(i=1; i<6; i++){                             //1.i从1开始, 是因为假设第二个数字是insert进去的;
		if(a[i] < a[i-1]){                          //如果当前要insert进去的值比前一个值小: 则要考虑insert到哪里(否则i+1继续新的循环);
			tmp = a[i];                             //设置此insert的值为tmp;
			for(j=i-1; j>=0 && a[j] > tmp; j--){    //2.j从i的前一个地方开始与tmp比较, 如果j代表的值大, 那么j+1被j覆盖;
				a[j+1] = a[j];
			}
			a[j+1] = tmp;                           //j--之后, 新j代表的值不大于(即小于)tmp了, 那么tmp要放在(j--)+1处;
		}
	}                                               //insert sort的逻辑是简单的, 代码中array的index安排是忐忑的..;

	for(int i = 0; i<6; i++){                       //输出..;
		printf("%d ", a[i]);
	}
	printf("\n");


	return 0;
}