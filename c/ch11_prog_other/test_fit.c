/* @UINVESRE.COM_20161222_HYE
 * test_fit.c: 截取字符串到指定
 * 大小.
 */

#include <stdio.h>
#include <string.h>

void fit(char *, unsigned int);

int main(){

    char mesg[] = "Things should be as simple as possible,"
                        "but not simpler.";
    fit(mesg, 20);
    puts(mesg);

    return 0;
}

void fit(char * msg, unsigned int size){
    if (strlen(msg) > size) {
        msg[size] = '\0';
    }
}