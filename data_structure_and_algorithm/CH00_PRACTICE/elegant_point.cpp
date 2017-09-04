/* @UNIVESRE.COM_20161220_HYE
 * 优雅点_Elegant Point: 小易有一个圆心在坐标原点的圆, 小易知道圆半径的平方. 小易认为在圆上
 * 的点, 如果横/纵坐标都是整数的点是优雅的; 小易现在想寻找一个算法计算出优雅的点的个数，请你来
 * 帮帮他. 例如: 半径的平方如果为25, 优雅点就有: (+/-3,+/-4), (+/-4,+/-3), (0,+/-5), 
 * (+/-5,0)一共12个.
 * 输入描述: 输入一个整数, 即圆半径的平方, 在32位int范围内.
 * 输出描述: 输出一个整数, 即为优雅的点的个数.
 * 输入例子: 25;
 * 输出例子: 12. 
 * END. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[]){

    //printf("The radius's power:\n");
    //int tmp = atoi(argv[2]);
    int tmp = 0;
    scanf("%d", &tmp);
    //printf("%d\n", tmp);
    double root = 0.0;
    root = sqrt(tmp);
    int count = 0;
    for(int i = -root; i < 0; i++){         //临界点1: 不取到;
        for(int j = -root; j <= 0; j++){    //临界点2: 取到(反正两个临界点有一个取到就好了);
            if((i*i + j*j - tmp) == 0 ) {   //如果是两个点是半径的平方;
                count++;                    //点的个数+1;
            }
        }
    }

    //如果每个象限都算一遍, 会超时, 那么就只好在临界点上限定一下, 然后乘以4(4个象限);
    count *= 4;

    printf("%d\n", count);

    return 0;
}