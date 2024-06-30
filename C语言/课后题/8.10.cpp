//#include<stdio.h>
//
//void main ()
//{
//	int n ;
//	int i , j ;
//	int Array[99][99]={};
//	int sum = 0;
//	printf("Please enter the time of this array : ");
//	scanf("%d",&n);
//	printf("Please enter your array(n*n): \n");
//	for (i = 0; i < n;i++)
//		for (j = 0;j < n;j ++)
//			scanf("%d",&Array[i][j]);
//	
//		for (i=0,j=0;i<n;j++,i++)
//		sum+=Array[i][j];
//		for (i=0,j=n-1;i<n;i++,j--)
//		sum+=Array[i][j];
//	
//		n%2==0 ? printf("SUM = %d\n",sum) : printf("SUM = %d\n",sum-Array[n/2][n/2]);
//}