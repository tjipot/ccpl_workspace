/* @UNIVESRE.COM_20161220_HYE
 * Jump跳石板: 小易来到了一条石板路前, 每块石板上从1挨着编号为: 1、2、3...
 * 这条石板路要根据特殊的规则才能前进: 对于小易当前所在的编号为K的石板, 
 * 小易单次只能往前跳K的一个约数步(不含1和K), 即跳到K+X(X为K的一个非1和本身
 * 的约数)的位置. 小易当前处在编号为N的石板, 他想跳到编号恰好为M的石板去, 小
 * 易想知道最少需要跳跃几次可以到达.
 * 例如: N = 4, M = 24: 4->6->8->12->18->24, 于是小易最少需要跳跃5次, 
 * 就可以从4号石板跳到24号石板.
 * 输入: 同在一行的两个整数N和M, 以空格隔开(4≤N≤100000, N≤M≤100000);
 * 输出: 小易最少需要跳跃的步数, 如果不能到达输出-1;
 * 输入例子:
 * 4 24
 * 输出例子:
 * 5 
 * End. */

#include <stdio.h>

/* 先声明: 占个位. */
int assumption1();
int assumption2();

/* 程序入口 */
int main(){

    assumption1();
    //    assumption2();

    return 0;
}

/* Assumption1: static stepping.
 * 思路: 跨的步数都是按照原来格子的约数进行跨步的,
 * 即便跨出去到了新的石板后, 也不按照新的石板
 * 的约数进行跨步, 故称之为静态跨步. */
int assumption1(){
    int num1 = 0, num2 = 0;
    printf("Give two values:\n");
    scanf("%d %d", &num1, &num2);
    int diff = num2 - num1;
    int stepCount = 0;

    for(int i = num1; i >= 1; i--){

        if(num1%i == 0){
            int step = diff/i;
            diff = diff - step*i;
            if(diff == 0){
                stepCount += step;
                printf("Result: %d\n", stepCount);
                return stepCount;
            }else{
                stepCount += step;
                continue;
            }
        }
    }

    return -1;
}

/* Assumption2: dynamic stepping.
 * 思路: 跨的步数是按照每次新的石板的约数
 * 进行动态计算的, 每次跨到新的石板后, 都
 * 重新计算石板的约数, 以进行动态跨步. */
int assumption2(){

    return -1;
}

/* 以下是Assumption1对应的网站给的反馈(参考): 根本就是牛头马嘴, 不是我这题的反馈;
 * 您的代码已保存
 *
 * case通过率为0.00%
 * 你的代码仅仅处理了一个测试用例，没有循环处理多个测试用例。
 * 比如对于求解A+B的和的题目，需要按照以下代码来处理
 * 
 * 正确代码：
 * #include <stdio.h>
 * int main() {
 *   int a,b;
 *   while(scanf("%d %d",&a, &b) != EOF)//注意while处理多个case
 *     printf("%d",a+b); //根据题目情况是否输出回车
 *   return 0;
 * }
 *
 * 错误代码:
 * #include <stdio.h>
 * int main() {
 *   int a,b;
 *   scanf("%d %d",&a, &b);//没有处理多个case
 *   printf("%d",a+b); //根据题目情况是否输出回车
 *   return 0;
 * }
 *
 * End. */

