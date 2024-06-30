/*
	 10.1
	 从键盘输入一些字符并把他们送到磁盘里去。	
 */

#include<stdio.h>
#include<stdlib.h>

int main()

{
	FILE* fp;
	char ch, filename[10];
	
	printf("Enter the file's name : ");
	scanf("%s",filename);
	
	fp = fopen(filename,"w");
	
	if(fp == NULL)
	{
		printf("wrong!!!!!\n");
		exit(0);
	}
	
	ch = getchar();
	
	printf("Enter a string : ");
	ch =  getchar();
	
	while(ch != '#')
	{
		fputc(ch,fp);
		putchar(ch);
		ch = getchar();
	}
	fclose(fp);
	putchar(10);
	
	return 0;
}


 /*
	 10.2
	文件的复制
 */

#include<stdio.h>
#incldue<stdlib.h>
int main ()
{
	FILE* in, *out;
	char ch, infile[10], outfile[10];
	
	printf("read file name ： ");
	scanf("%s",infile);
	printf("write file name : ");
	scanf("%s",outfile);
	
	in = fopen(infile,"r");
	out = fopen(ourfile,"w");
	
	if(in = NULL ||out = NULL)
	{
		printf("File open failed ! \n");
		exit(0);
	}
	
	while(!feof(in))
	{
		ch = fgetc(in);
		fputc(ch,out);
		putchar(ch);
	}
	
	putchar(10);
	fclose(in);
	fclose(out);
	return 0;
	
}


/*
	10.3.1
	从键盘输入一些字符串，对他们按照字母大小排序
	把排完序的字符串输入到文本文件中
	输出字符串
*/

#include<stdio.h>
#include<stdlib.h>

int main ()
{
	FILE* fp;
	char str[3][10], temp[10];
	int i, j, k, n = 3;
	printf("Enter three strings : ");
	for(i = 0;i < 3;i++)
		gets(str[i]);
	for(i = 0;i < 3;i ++)
	{
		k = i;
		for(j = i + 1;j < 3;j ++)
		{
			if(strcmp(str[k]))
			{
				strcpy(temp,str[i]);
				strcpy(str[i],str[j]);
				strcpy(str[j],temp);
			}
		}
	}
	
	fp = fopen("G:\Cfile\1.txt","w");
	if(fp == NULL)
	{
		printf("Open wrong !!!! \n");
		exit(0);
	}
	
	printf("The new result : ");
	
	for(i = 0;i < 3;i ++)
	{
		fputs(str[i],fp);
		fputs("\n",fp);
		printf("%s\n",str[i]);
	}
	return 0;
}

/*
	10.3.2
	从磁盘中读取刚才已经排好序的，在文件中的字符串
*/

#include<stdio.h>

int main ()
{
	FILE* fp;
	char str[3][10];
	int i = 0;
	fp = fopen("g:\Cfile\1.txt","w");
	if(fp ==NULL)
	{
		printf("Open wrong !!\n");
		exit(0);
	}
	
	while(fgets(str[i],10,fp)!=NULL)
	{
		printf("%s",str[i]);
		i ++;
	}
	fclose(fp);
	return 0;
}

/*
	10.4.1
	从键盘上输入10个学生的有关数据，然后将他们转存到磁盘上去
*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

struct student_type
{
	char name[10];
	int num;
	int age;
	char addr[15]
}stud[SIZE];

void save()
{
	FILE* fp;
	int i;
	fp = fopen("stu.dat","wb");
	if(fp == NULL)
	{
		printf("Can't open ths file!!!\n");
		return 0;
	}
	
	for(i = 0;i < SIZE;i ++)
	{
		if(fwrite(&stdu[i],sizeof(struct student_type),1,fp) != 1)
		printf("file write error !!! \n");
	}
	
	fclose(fp);
}

int main()
{
	int i;
	printf("Enter a data of student :\n");
	for(i = 0;i < SIZE;i ++)
		scanf("%s%d%d%s",stdu[i].name, stdu[i].num, stdu[i].age, stdu[i].addr);
	save();
	return 0;
}

/*
	10.4.2
	向屏幕中输出上面的那些成绩。
*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

struct student_type
{
	char name[10];
	int num;
	int age;
	char addr[15];
}stud[SIZE];

int main()
{
	int i;
	FILE* fp;
	fp = fopen("stu.dat","rb");
	if(fp == NULL)
	{
		printf("File open error !!\n");
		exit(0);
	}
	for(i = 0;i < SIZE;i ++)
	{
		fread(&stud,sizeof(struct student_type),1,fp);
		printf("%-10s %4d %4d %-15s\n",stud[i].name,stud[i].num, stud[i].age, stud[i].addr);
	}
	fclose(fp);
	return 0
}

/*
	10.4.3
	从已经存在的二进制文件中读入数据并输出到另一个文件中。
*/

#incldue<stdio.h>
#include<stdlib.h>

void load()
{
	FILE* fp;
	int i;
	fp = fopen("stu.dat","rb");
	if(fp == NULL)
	{
		printf("Open wrong !!!!!\n");
		return;
	}
	for(i = 0;i < SIZE;i ++)
	{
		if(fread(&stud[i],sizeof(struct student_type),1,fp) != 1)
		{
			if(feof(fp))
			{
				fclose(fp);
				return;
			}
			printf("read error!!\n");
		}
	}
	fclose(fp);
}

int main ()
{
	load();
	save();
	return 0;
}


/*
	10.5
	将一个磁盘文件中的信息第一次显示在屏幕上，第二次复制到另一个文件上
*/

#include<stdio.h>

int main ()
{
	FILE* fp1, *fp2;
	fp1 = fopen("stu.dat","r");
	fp2 = fopen("stu1.dat","w");
	while(!feof(fp1))
		putchar(getfp1);
	putchar(10);
	rewind(fp1);
	while(!feof(fp1))
		putc(getc(fp1),fp2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}


/*
	10.6
	从磁盘上的学生数据中读取第1，3，5，7，9个学生的数据 
*/

#incldue<stdio.h>
#incldue<stdlib.h>
struct stable_partition
{
	char name[10]
	int num;
	int age;
	char addr[15];
}stud[10];

int main ()
{
	int i;
	FILE* fp;
	fp = fopen("stu.dat","rb");
	if(fp == NULL)
	{
		printf("Can not oprn the file !!!\n");
		return 0;
	}
	for(i = 0;i < 10;i +=2)
	{
		fseek(fp, i*sizeof(struct st),0);
		fread(&stud[i],sizeof(struct st),1,fp);
		printf("%-10s %4d %4d %-15s\n",stud[i].name, stud[i].num, stud[i].age, stud[i].addr);
	}
	fclose(fp);
	return 0;
}

