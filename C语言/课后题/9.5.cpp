//
//// 因老师说用函数作为地址没必要，故未按照题目的要求做
//
//#include<stdio.h>
//#define DELTA 0.000001
//
//int main ()
//{
//	float delta;
//	float result1 = 0,result2 = 0;
//
//	for(float i = 0;i < 1;i = i+DELTA)
//		result1 += DELTA*(1 + i*i);
//	for(float i = 0;i < 3;i = i+DELTA)
//		result2 += DELTA*(i/(i*i + 1));
//	printf("NO.1's squre is %.5f\n",result1);
//	printf("NO.2's squre is %.5f\n",result2);
//	return 0;
//
//}