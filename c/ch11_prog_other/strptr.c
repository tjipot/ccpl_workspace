/* @UNIVESRE.COM_20161221_HYE
 * strptr.c: 把字符串看作指针. */

#include <stdio.h>
int main(){

    //注意字串是如何被格式化符号解读的: 字串, 地址, 地址指向的对象;
    printf("%s %p %c\n", "We", "are", *"space farers"); //%c也可以替换成%d: 's'的ascii值为115;

    return 0;
}