//#include<stdio.h>
//
//void Swap(int *a,int *b);
//void Exchange(int *a,int *b,int *c);
//
//void main ()
//{
//	int a , b , c ; 
//	printf("Enter 3 numbers : ");
//	scanf("%d%*c%d%*c%d",&a, &b, &c);
//	Exchange(&a,&b,&c);
//	printf("a = %d\nb = %d\nc = %d\n",a,b,c);
//}
//
//void Exchange(int *a,int *b,int *c)
//{
//	if(*a < *b)  Swap(a,b) ;
//	if(*a < *c)  Swap(a,c) ;
//	if(*b < *c)  Swap(b,c) ;
//}
//
//void Swap(int *a,int *b)
//{
//	int t ;
//	t = *a;
//	*a = *b;
//	*b = t;
//}