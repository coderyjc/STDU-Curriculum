#include<stdio.h>
int main ()
{
	int a[10];
	int i, j, k, n, t;

	scanf("%d",&n);
	for(i = 0; i < n; i++)
		scanf("%d",&a[i]);

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

		if(n == 1)
		{
			printf("%d",a[0]);
			break;
		}

		if(i == n-1) break;

		for(k = 0;k < n;k ++)
		{
			if (k == n - 1)
				printf("%d",a[k]);
			else 
				printf("%d ",a[k]);
		}
		printf("\n");
	}
}