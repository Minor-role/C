#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST

void showtime(long);
void show_info(struct utmp *);

int main(int argc, char const *argv[])
{
	struct  utmp current_record; // 把信息读到里面去
	int utmpfd; // 把描述符读到里面去
	int reclen = sizeof(current_record);
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd,&current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
/*
*	显示登录信息
*/
{
	if (utbufp->ut_type != USER_PROCESS)
		return;
	printf("% - 8.8s",utbufp->ut_name);
	printf(" ");
	printf("% - 8.8s",utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);
	#ifdef SHOWHOST
	printf("% - 8.8s",utbufp->ut_host);
	#endif
	printf("\n");

}

void showtime(long timeval)
/*
* 	通过ctime函数转换时间
*/
{
	char *cp;
	cp = ctime(&timeval);
	printf("% 12.12s", cp+4);
}