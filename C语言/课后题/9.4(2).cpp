//#include<stdio.h>
//void MonthDay(int year, int yearDay, int *pMonday, int *pDay);
//int main ()
//{
//	int year, yearDay, Month, Day;
//	puts("Enter this which day of which year(type XXXX.XXX) ��");
//	scanf("%d.%d",&year,&yearDay);
//	MonthDay(year, yearDay, &Month, &Day);
//	printf("It is %d.%d.%d\n", year, Month, Day);
//}
//
//void MonthDay(int year, int yearDay, int *pMonth, int *pDay)
//{
//	int i, monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//	if(year%400==0||year%100!=0&&year%4==0)	monthday[1]++; // ���������Ļ�����2�µ�����+1
//	for(i = 0;	;i ++)
//	{
//		yearDay -= monthday[i];   //ÿѭ��һ�Σ����ܵ�������ȥ��һ�µ�����
//		if(yearDay <= 0)			//���С��0�ˣ��ټӻ�����Ȼ���˳�ѭ��
//		{
//			yearDay += monthday[i];
//			break;
//		}
//	}
//	*pMonth = i + 1 ;			//�õ�ַ�е�ֵ����i+1,��Ϊi�Ǵ�0��ʼ��
//	*pDay = yearDay ;			
//}