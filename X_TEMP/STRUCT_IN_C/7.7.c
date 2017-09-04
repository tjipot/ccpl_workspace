#include <stdio.h>

int main(void){

	union data{
		int i;
		char a[2];
	}*p, u;

	p = &u;
	p->i = 0;
	p->a[0] = 0x38;
	p->a[1] = 0x39;

	printf("p->i:%x\n", p->i);
	printf("u-Size: %ld\n", sizeof(u));

	return 0;
}
