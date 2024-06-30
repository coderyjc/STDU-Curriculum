//#include<stdio.h>
//
//void fun(void (*p)(int x,int y),int a,int b);
//void min(int x,int y);
//void max(int x,int y);
//void add(int x,int y);
//
//void main()
//{
//	int a , b;
//	int i;
//	printf("Enter 2 numbers : ");
//	scanf("%d%*c%d",&a,&b);
//	printf("Enter 1 ==> min\nEnter 2 ==> max\nEnter 3 ==> add\n");
//	scanf("%d",&i);
//	switch(i)
//	{
//	case 1 : fun(min,a,b) ; break ;
//	case 2 : fun(max,a,b) ; break ;
//	case 3 : fun(add,a,b) ; break ;
//	}
//}
//
//void fun(void (*p)(int x,int y),int a,int b)
//{
//	(*p)(a,b);
//}
//void min(int x,int y)
//{
//	printf("The smaller is %d\n",x<y?x:y);
//}
//void max(int x,int y)
//{
//	printf("The greater is %d\n",x>y?x:y);
//}
//void add(int x,int y)
//{
//	printf("%d + %d = %d\n",x,y,x+y);
//}
