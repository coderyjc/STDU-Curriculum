//#include<stdio.h>
//
//union cate
//{
//	int clas;
//	char position[20];
//};
//
//struct member
//{
//	long number;
//	char name[20];
//	char sex;
//	char job;
//	union cate pos;
//};
//
//int main ()
//{
//	struct member a[2];
//	for(int i = 0;i < 2;i ++)
//	{
//		scanf("%ld %s %c %c",&a[i].number,a[i].name,&a[i].sex,&a[i].job);
//		if(a[i].job == 's'||a[i].job == 'S' )
//			scanf("%d",&a[i].pos.clas);
//		else if(a[i].job == 't'||a[i].job == 'T')
//			scanf("%s",a[i].pos.position);		
//		else 
//		printf("Enter error!!\n");
//	}
//
//	for(int i = 0;i < 2;i++)
//	{
//		printf("%ld %s %c %c ",a[i].number,a[i].name,a[i].sex,a[i].job);
//		if(a[i].job == 's'||a[i].job == 'S' )
//			printf("%d\n",a[i].pos.clas);
//		else if(a[i].job == 't'||a[i].job == 'T')
//			printf("%s\n",a[i].pos.position);		
//	}
//	return 0;
//}