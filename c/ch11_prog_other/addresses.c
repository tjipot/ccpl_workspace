/* @UNIVESRE.COM_20161221_HYE
 * addresses.c: 字符串地址. */

#define MSG "I'm special"

#include <stdio.h>
int main(){

    char ar[] = MSG;
    const char * pt = MSG;

    printf("Address of \"I'm special\": %p \n", "I'm special");
    printf("Address ar:               %p\n", ar);
    printf("Address pr:               %p\n", pt);
    printf("Address of MSG:           %p\n", MSG);
    printf("Address of \"I'm special\": %p \n", "I'm special");

    /* Results: 说明编译器对同一个字串的多个使用也会优化, 使用同一个在数据区的字串;
     * Address of "I'm special": 0x106206f10
     * Address ar:               0x7fff599f9b5c
     * Address pr:               0x106206f10
     * Address of MSG:           0x106206f10
     * Address of "I'm special": 0x106206f10
     */

    return 0;
}

