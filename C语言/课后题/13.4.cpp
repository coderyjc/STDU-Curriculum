//#include<stdio.h>
//int main ()
//{
//	char name1[20], name2[20];
//	printf("Enter the read file's name :");
//	scanf("%s",name1) ;
//	printf("Enter the write file's name :" );
//	scanf("%s",name2);
//
//	FILE *fp1, *fp2 ;
//	fp1 = fopen(name1,"r") ;
//	fp2 = fopen(name2,"w") ;
//
//	if(fp1 == NULL || fp2 == NULL)
//		printf( "wrong!!" );
//
//	char ch;
//	while(!feof(fp1))
//	{
//		ch = fgetc(fp1);
//		fputc(ch,fp2);
//		putchar(ch);
//	}
//
//	fclose(fp1);
//	fclose(fp2);
//	return 0;
//}