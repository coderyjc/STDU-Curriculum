//#include<stdio.h>
//#include<stdlib.h>
//#define LEN sizeof(struct student) // LEN �Ĵ�С�ǽṹ��Ĵ�С
//
//struct student
//{
//	long num ;
//	float score;
//	struct student *next;	//ָ����һ���ڵ�
//};
//
//int n;
//struct student *creat(void)
//{
//	struct student *head, *p1, *p2;	//head��ͷ��� 
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
//		p1 = (struct student*)malloc(LEN); // p1�����ڿ��ٽڵ㣬p2����ָ���µĽڵ㡣
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
