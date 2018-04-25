/**编译原理作业：词法分析程序
作者：Ian
时间：2017年10月13日14:02:06
变量解释：
k：关键字表
P：分界符表
ci：存放常数
id：存放标识符
instring：输入源程序的单词缓存
outtoken：输出内部表示缓存
步骤：

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "test.h"

char k[Middle][Min];// 关键字表 
char p[Middle][Min];// 分界符表
char ci[Middle][Max]; // 常数表
char id[Max][Middle]; // 标识符表
char instring[Max]; // 输入源程序的单词缓存
int counter = 0;

list *head, *p1,*p2; // Token串的头指针和移动指针

int read_signal(char *path, char(*temp)[Min])
{
	/* 把符号表读进数组 */
	int i = 0, j = 0;
	char ch;
	FILE *fp;
	fp = fopen(path, "r");
	ch = fgetc(fp); // 获取初始输入
	while (ch != EOF)
	{
		for (; ch != ' ' && ch != EOF; j++)
		{
			/* 将字符读入数组 */
			*(*(temp + i)+j) = ch;
			ch = fgetc(fp);
		}
		*(*(temp + i) + j) = '\0'; //结束符
		// 跳到数组下一个变量
		i++;
		j = 0;
		while (ch == ' ')// 把空格去掉
			ch = fgetc(fp);
	}
	fclose(fp);
	return i--;
}

int DFA_constant(FILE *fp)
{
	/* DFA判断常数符 */

}

char DFA_keyword_identifier(FILE *fp, char(*temp)[Min], char onechar,int k)
{
	/* DFA判断关键字及标识符 */
	char ch;
	int i = 0;
	int cot = 0;//计数器
	ch = onechar;
	while (isalnum(ch)|| ch == '_')
	{
		instring[i] = ch;
		ch = fgetc(fp);
		i++;
	}
	instring[i] = '\0'; 
	//printf("%s", instring);
	for (; cot < k; cot++) //跟关键字表比较
	{
		if (strcmp(instring, temp + cot) == 0) // 如果是关键字，则记录下来
		{
			p1 = (list*)malloc(sizeof(list));
			strcpy(p1->word, instring);
			p1->i = 1; // 关键字类号
			break;
		}	
	}
	if (cot == k)
	{
		p1 = (list*)malloc(sizeof(list));
		strcpy(p1->word, instring);
		p1->i = 6; // 标识符类号
	}

	p2->next = p1;
	p2 = p1;
	p1->next = NULL;
	memset(instring, '\0', Max); // 重新初始化缓冲串
	return ch;
}

int lexical(FILE *fp , char (*keyword)[Min], char(*delimiter)[Min], char(*constant)[Min],int k,int d, int c)
{
	/* 词法分析 */

	char ch; // 缓冲字符
	ch = fgetc(fp);
	while (ch == ' ') // 清除空格
		ch = fgetc(fp);
	while (ch != EOF)
	{
		if (isalpha(ch))
		{
			//如果是字母，则进入关键字和标识符的DFA
			ch = DFA_keyword_identifier(fp, keyword, ch, k);
		}
		else if (isdigit(ch))
		{
			//如果是数字，则进入常数的DFA
			ch = DFA_constant(fp, constant);
		}
		else if ()
			ch = fgetc(fp);
	}
	return 0;
}


int main()
{
	/* 主函数 */

	FILE *fp; // 目标源文件指针
	char tarpath[Middle];
	int k, d, c; // 每个符号表的长度

	// 符号表的路径
	char keypath[] =  "keyword.txt" ;
	char dlipath[] =  "delimiter.txt";
	char conpath[] =  "constant.txt";

	// 将符号表缓存到数组
	char keyword[Middle][Min];// 关键字表 
	char delimiter[Middle][Min];// 分界符表
	char constant[Middle][Min]; // 常数表
	k = read_signal(keypath, keyword);
	d = read_signal(dlipath, delimiter);
	c = read_signal(conpath, constant);

	// 初始化Token串
	head = (list*)malloc(sizeof(list));
	p1 = p2 = head;


	printf("Please enter a name of your source file: ");
	gets_s(tarpath,Middle);
	fp = fopen("source.txt", "r");

	lexical(fp,keyword,delimiter,constant,k,d,c);

	//测试符号表是否成功读入
	//test_sign(k,keyword);
	//test(d, delimiter);
	//test(c, constant);
	// 测试关键字是否识别成功
	test_DFA_keyword_identifier(head->next);
	system("pause");
	return 0;
}
