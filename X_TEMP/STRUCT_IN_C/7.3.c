#include <stdio.h>
struct student_info
{
	char name[20];
	int id;
	char phone[12];
}student;

struct student_info stuArray[3] = {
	{"Haoran1", 10, "12345678910"},
	{"Haoran2", 11, "12312312312"},
	{"Haoran3", 12, "45645645645"}
};

int main(){
	for(int i = 0; i < 3; i++){
		printf("Stu Name: %s, Stu Id: %d, Stu Phone: %s.\n", stuArray[i].name, stuArray[i].id, stuArray[i].phone);
	}

	return 0;
}
