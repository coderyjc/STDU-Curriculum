//#include<stdio.h>
//int a = 0; 
//void Ac(int x);
//void Fun()
//{
//	printf("%d\n",a); //这里不输出a
//}
//
//void main ()
//{
//	a = 8;	//如果在这里不给a赋值，那么输出的a是全局变量里的a
//			//如果给a赋值了，那么输出的a就是在这个函数块里的a
//	printf("%d\n",a);
//
//	Ac(a);	//如果把值传递给了一个函数，那么a的值还是在mian中已经赋好了的值
//}
//
//void Ac(int a)
//{
//	a = a-5 ;
//		printf("%d",a);
//}