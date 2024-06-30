//#include<stdio.h>
//#include<string.h>
//
//int ID[30],m,n,i,j;
//float score[30][30],score2[30][30];
//char name[30][10];
//
//void Read()
//{
//	printf("input m,n:");
//	scanf("%d%d",&m,&n);
//	for(i=0;i<m;i++)
//	{
//		scanf("%d%s",&ID[i],name);
//	}
//	for(i=0;i<m;i++)
//	{
//		for(j=0;j<n;j++)
//		{
//			scanf("%f",&score[i][j]);
//			score2[i][j]=score[i][j];
//		}
//	}
//}
//void sum2(int m,int n,float score2[][30],float psum2[],float aver2[])
//{
//	for(i=0;i<m;i++)
//	{
//		psum2[i]=0;
//		for(j=0;j<n;j++)
//			psum2[i]+=score2[i][j];
//		aver2[i]=psum2[i]/n;
//	}
//}
//void find2(float psum2[],char name1[][10],float score2[][30],int m,int n)
//{
//	int k;
//	float temp;
//	char b[30];
//	printf("Input name:");
//	scanf("%s",&b);
//	printf("\0");
//	for(i=0;i<m-1;i++)
//	{
//		for(j=i+1;j<m;j++)
//		{
//			if(psum2[i]<psum2[j])
//			{
//				temp=psum2[i];
//				psum2[i]=psum2[j];
//				psum2[j]=temp;
//			}
//		}
//	}
//	for(i=0;i<m;i++)
//		score2[i][30]=i+1;
//	for(i=0;i<m;i++)
//	{
//		if(strcmp(b,name1[i])==0)
//		{
//			for(k=0;k<n;k++)
//				printf("%.1f\t",score2[i][k]);
//			printf("%.1f\n",score2[i][30]);
//		}
//	}
//
//}
//int main()
//{
//	float psum1[30],psum2[30],aver1[30],aver2[30];
//	Read();
//	sum2(m,n,score2,psum2,aver2);
//	find2(psum2,name,score2,m,n);
//	return 0;
//}
