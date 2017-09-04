/* @UNIVESRE.COM_16-12-31_POSIX,
 * count.c: 使用标准IO. */

#include <stdio.h>
#include <stdlib.h>         //exit()原型;

int main(int argc, char * argv[]){

    int ch;                 //存储每个字符的地方;
    FILE *fp;               //文件指针: UNIX特性, OS说的, 你得服;
    unsigned long count = 0;

    if(argc != 2){          //检查参数个数;
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE); //Macro in "stdlib.h";
    }

    if((fp = fopen(argv[1], "r")) == NULL){ //检查文件打开情况;
        printf("Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while((ch = getc(fp)) != EOF){
        putc(ch, stdout);   //与putchar(ch)相同;
        count++;
    }

    fclose(fp);
    printf("\nFile %s has %lu characters\n", argv[1], count);

    return 0;
}