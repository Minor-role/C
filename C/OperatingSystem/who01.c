#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>

#define SHOWHOST

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

show_info(struct utmp *utbufp)
/*
*	显示登录信息
*/
{
	printf("% - 8.8s",utbufp->ut_user);
	printf(" ");
	printf("% - 8.8s",utbufp->ut_line);
	printf(" ");
	printf("%10ld",utbufp->ut_time);
	printf(" ");
	#ifdef SHOWHOST
	printf("% - 8.8s",utbufp->ut_host);
	#endif
	printf("\n");

}