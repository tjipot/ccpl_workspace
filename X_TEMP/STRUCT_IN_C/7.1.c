#include <stdio.h>
//Exercise_7.1
struct complex_struct
{
	int real;
	int virtual;
};

struct complex_struct complexAdd(struct complex_struct *s1, struct complex_struct *s2)
{
	struct complex_struct tmp1;
	tmp1.real = (*s1).real + (*s2).real;
	tmp1.virtual = (*s1).virtual + (*s2).virtual;
	return tmp1;
}

struct student
{
	int number;
	char name[20];
	char sex;
	int age;
};

int main(void){

//	struct student stu1;
//	struct student stu2;
	struct complex_struct tmp;
	struct complex_struct cs1;
	struct complex_struct cs2;
	tmp.real = 1;
	tmp.virtual = 2;
	cs1 = tmp;
	cs2 = tmp;
	
	tmp = complexAdd(&cs1, &cs2);
	printf("The Result: %dreal, %dvirtual\n", tmp.real, tmp.virtual);

	return 0;
}



