#include<stdio.h>
int main ()
{
	int a[10];
	int i, j, k, n, t;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < n; i++)
	{
		for(j = 0;j < n - i - 1;j ++)
		{
			if(a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
		for(k = 0;k < n;k ++)
		{
			(k == n - 1) ? printf("%d",a[k]) : printf("%d ",a[k]) ;
		}
		printf("\n");
	}
}