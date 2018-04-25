// 改进版的who，读取utmp文件信息，使用了缓冲技术，减少了程序的访问时间
// 缓冲技术：一次性将更多的内容从文件读到内存，而不是多次从文件读取
// 缓冲技术出现的原因：访问更少次数磁盘，更重要的是->减少管理员模式和用户模式相互转换所需要的时间
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *) NULL)
#define UTSIZE (sizeof(struct  utmp))

static char utmpbuf[NRECS * UTSIZE] // 缓冲区
static int num_recs; // 记录数
static int cur_rec; // 下一个结构体
static int fd_utmp = -1; // 需读文件的文件描述符

utmp_open(char *filename)
{
	fd_utmp = open(filename, O_RDONLY);
	cur_rec = num_recs = 0;
	return fd_utmp;
}

struct utmp * utmp_next()
/*
*	将文件内容读入内存，并返回内存地址指针
*/
{
	struct utmp * recp;
	if(fd_utmp == -1) // 文件描述符-1表示打开失败
		return NULLUT;

	if(cur_rec == num_recs && utmp_reload() == 0) // 记录没有读到缓冲区，证明没记录
		return NULLUT;

	recp = (struct utmp*) &utmpbuf[cur_rec * UTSIZE]; // 获得下一条记录的地址
	cur_rec++;
	return recp;
}

int utmp_reload()
/*
*	将多条记录读到缓冲区
*/
{
	int amt_read;
	amt_read = read(fd_utmp,utmpbuf, NRECS * UTSIZE);
	num_recs = amt_read/UTSIZE; // 获得记录条数
	cur_rec = 0;
	return num_recs;
}

utmp_close()
{
	if(fd_utmp != -1)
		close(fd_utmp);
}

