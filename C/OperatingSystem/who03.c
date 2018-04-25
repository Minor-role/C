#include<stdio.h>
#include<sys/types.h>
#include<utmp.h>
#include<fcntl.h>
#include<time.h>

#define SHOWHOST

void show_info(struct utmp*);
void showtime(time_t);

int main(int argc, char const *argv[])
{
	struct utmp* utbufp,
		*utmp_next();

	if(utmp_open(UTMP_FILE) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while((utbufp = utmp_next()) != ((struct utmp*) NULL))
		show_info(utbufp);
	utmp_close();
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