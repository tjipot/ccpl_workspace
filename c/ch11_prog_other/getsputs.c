/* @UNIVESRE.COM_20161222_HYE
 * getsputs.c: 使用gets和puts().
 */

#include <stdio.h>

#define STLEN 5

int main(void){

    char words[STLEN];

    puts("Enter a string, pls:");
    //gets()的唯一参数是words, 无法检查数组是否装得下输入行的内容, 可能会导致缓冲区溢出(buffer overflow);
    gets(words);

    printf("Your string twice:\n");
    printf("%s\n", words);
    puts(words);
    puts("Done.");

    /* Results:
     * Enter a string, pls:
     * warning: this program uses gets(), which is unsafe.
     * I want to walk!
     * Your string twice:
     * I want to walk!
     * I want to walk!
     * Done.
     */

    return 0;
}