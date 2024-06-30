//#include<stdio.h>
//
//struct student 
//{
//	int number;
//	float score;
//	struct student* next;
//}a,b,c;
//
//int main ()
//{
//	a.number = 10000;a.score = 89;a.next = &b;
//	b.number = 10001;b.score = 98;b.next = &c;
//	c.number = 10002;c.score = 88;c.next = NULL;
//	struct student *p = &a;
//	do{
//		printf("%ld%5.1f\n",p->number,p->score);
//		p = p->next;
//	}while(p != NULL);
//	return 0;
//}