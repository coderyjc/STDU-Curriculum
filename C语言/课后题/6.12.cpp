//
////yanjingcun   2019.10.22
//
//#include <stdio.h>
//
//int main ()
//
//{
//	int s , a ;					 //s代表数据的总和；a是每一项输入的值
//
//	for ( s = 0 , a = 0 ;  ; )   //s和a的初始值都赋为 0 
//	{
//		printf("Please enter a number greater than zero : ");
//		scanf("%d",&a);			 //输入一个数字，赋值给a
//
//		if ( a <= 0 )	break ;	 //如果这个数字是小于0的，就直接跳出循环，输入结束
//		else s = s + a ;		 //如果大于0 ，就让总和加上它
//	}
//
//	printf("The sum of these number is :%d ",s);	//最后输出总和的值
//
//	return 0 ;
//
//}
