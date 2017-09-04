/* @UNIVESRE.COM_20161221_HYE
 * p_and_s.c: 指针和字符串. */

#include <stdio.h>

int main(void){

    const char * mesg = "Don't be a fool!";
    const char * copy;

    copy = mesg;
    printf("%s\n", copy);
    printf("mesg = %s; &mesg = %p; value = %p\n", mesg, &mesg, mesg);
    printf("copy = %s; &copy = %p; value = %p\n", copy, &copy, copy);

    /* Results: 说明两个指针变量保存着相同的地址值, 而这两个指针变量的内存对象在不同的地址上;
     * Don't be a fool!
     * mesg = Don't be a fool!; &mesg = 0x7fff56aa5b60; value = 0x10915af42
     * copy = Don't be a fool!; &copy = 0x7fff56aa5b58; value = 0x10915af42
     */

    return 0;
}
