#include<stdio.h>
#define PAGELEN 24 // 每一页的宽度
#define LINELEN 512 // 每一行的长度

void do_more(FILE *);
int see_more();
int main(int ac, char const *av[])
{
	FILE *fp;
	if(ac == 1) // 如果文件数是一个，直接读入就OK
		do_more(stdin); // 这应该表示，将stdin缓冲区的信息都送到do_more函数
	else  // 如果需要显示的文件数是多个，则需要一个一个文件内容进行显示
		while(--ac)
			if((fp = fopen(* ++av,"r")) != NULL)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}

void do_more(FILE *fp)
/*
*	从文件中读取，并输出到终端，然后等到进一步调用
*	先输出 PAGELEN 行，序号35控制，再等待终端
* ，然后reply作为一个倒数计数器，使输出行数 = reply
*	num_of_lines一旦到达 PAGELEN，就会停下来等待输入
*/
{
	char line[LINELEN]; // 行缓冲区
	int num_of_lines = 0; // 输出的行数
	int see_more(),reply; // 返回需要继续输出的行数
	while(fgets(line,LINELEN,fp)) // 将第LINELEN行的数据读入到line
	{
		if (num_of_lines == PAGELEN)
		{
			reply = see_more(); // 获得键盘输入返回的行数
			if(reply == 0)
				break;
			num_of_lines -= reply; // 
		}
		if (fputs(line,stdout) == EOF)
			exit(1);
		num_of_lines ++;
	}
}

int see_more()
/*
*	打印信息，等待回复，在行结束返回#
*	q：结束，空格：继续，回车：一行
*/
{
	int c;
	printf("\033[7m more? \033[m");
	while((c = getchar())!= EOF)
	{
		if (c == 'q')
			return 0;
		if (c == ' ')
			return PAGELEN;
		if (c == '\n')
			return 1;
	}
	return 0;
}