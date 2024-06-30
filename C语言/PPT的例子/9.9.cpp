//#include<stdio.h>
//#include<stdlib.h>
//#define LEN sizeof(struct student) // LEN 的大小是结构体的大小
//
//struct student
//{
//	long num ;
//	float score;
//	struct student *next;	//指向下一个节点
//};
//
//int n;
//struct student *creat(void)
//{
//	struct student *head, *p1, *p2;	//head是头结点 
//	n = 0;
//	p1 = p2 = (struct student*)malloc(LEN);
//	scanf("%ld,%f",&p1->num,&p1->score);
//	head = NULL;
//	while(p1->num!=0)
//	{
//		n = n+1;
//		if(n == 1) head = p1;
//		else p2->next = p1;
//		p2 = p1;
//		p1 = (struct student*)malloc(LEN); // p1总是在开辟节点，p2总是指向新的节点。
//		scanf("%ld,%f",&p1->num,&p1->score);
//	}
//	p2->next = NULL;
//	return (head);
//}
//
//int main ()
//{
//	struct student *pt;
//	pt = creat();
//	printf("\nnum:%ld\nscore:%5.1f\n",pt->num,pt->score);
//	return 0;
//}
