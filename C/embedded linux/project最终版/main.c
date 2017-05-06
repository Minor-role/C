#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
// ����Ҫʹ������ͷ�Ľӿں���
#include "api_v4l2.h"

#define  ONE_CONNECT          1
#define  ONE_DISCONNECT       0
// ʹ�ú궨��ȥ����ϵͳ�ļ���״̬
// ��չ�Ժ�ǿ
#define G_WELCOME      1
#define G_LOGIN        2
#define G_MAIN         3
#define G_CAMERA       4
#define G_VIDEO        5
#define G_PHOTO        6
#define G_GAME         7
int wififd;
int wififlag=0;
int loginflag=0;
// ����һ��������¼�����ƫ��
int g_off_t=0;
// ����һ��������¼ϵͳ��״̬
int g_sys_state=1;
// ����һ���ַ����͵�����������
char password[6];
// ����һ����ά������ͼƬ��·��
char bmppath[10][30]=
{
	"/wuyi/num/0.bmp",
	"/wuyi/num/1.bmp",
	"/wuyi/num/2.bmp",
	"/wuyi/num/3.bmp",
	"/wuyi/num/4.bmp",
	"/wuyi/num/5.bmp",
	"/wuyi/num/6.bmp",
	"/wuyi/num/7.bmp",
	"/wuyi/num/8.bmp",
	"/wuyi/num/9.bmp",
};
// ��ʾ��¼����ĺ���
void show_login()
{
	show_fullbmp("/wuyi/loginmenu.bmp");
	show_anybmp(230,140,64,64,"/wuyi/num/1.bmp");
	show_anybmp(230+96,140,64,64,"/wuyi/num/2.bmp");
	show_anybmp(230+96*2,140,64,64,"/wuyi/num/3.bmp");
	show_anybmp(230,140+70,64,64,"/wuyi/num/4.bmp");
	show_anybmp(230+96,140+70,64,64,"/wuyi/num/5.bmp");
	show_anybmp(230+96*2,140+70,64,64,"/wuyi/num/6.bmp");
	show_anybmp(230,140+70*2,64,64,"/wuyi/num/7.bmp");
	show_anybmp(230+96,140+70*2,64,64,"/wuyi/num/8.bmp");
	show_anybmp(230+96*2,140+70*2,64,64,"/wuyi/num/9.bmp");
	show_anybmp(230,140+70*3,64,64,"/wuyi/num/del.bmp");
	show_anybmp(230+96,140+70*3,64,64,"/wuyi/num/0.bmp");
	show_anybmp(230+96*2,140+70*3,64,64,"/wuyi/num/enter.bmp");
}
// ��ʾ��������������
int add(int n)  //  n��2
{
	if(g_off_t<6)
	{
		// ��ʾ�������������
		show_anybmp(265+g_off_t*64,75,64,64,bmppath[n]);
		// ��ʱ
		usleep(50000);
		show_anybmp(265+g_off_t*64,75,64,64,"/wuyi/num/xing.bmp");//�ڵ�����
		
		// ���������������뱣������
		password[g_off_t]=n+'0';   // ����n����ַ�'n'
		g_off_t++; 
	}
}
// 
int del()
{
	if(g_off_t>0)
	{
		//���۷�
		show_anybmp(265+(g_off_t-1)*64,75,64,64,"/wuyi/num/black.bmp");
		//��������д��������
		password[g_off_t-1]='\0';
		g_off_t--;
	}
}
int enter()
{
	int fd;
	char buf[6];
	// ��ϵͳ�д����ȷ������ĵ�
	fd=open("/wuyi/passwd.txt",O_RDWR);
	if(fd==-1)
	{
		printf("open passwd.txt failed!\n");
		return -1;
	}
	// ��ȡ�����ŵ���ȷ����
	read(fd,buf,6);
	close(fd);
	// �Ա�����
	if(strcmp(buf,password)==0)
	{
		g_sys_state=G_MAIN;
	}
	else
	{
		loginflag=1;
		system("madplay /wuyi/1.mp3");
	}
}
// ��װʵ�ֻ�ӭ���湦�ܵĺ���
void do_welcome()
{
	//��ʾ��ӭ����
	show_fullbmp("/wuyi/welcome.bmp");
	//�޸�ϵͳ��״̬
	if(wififlag==1)
		g_sys_state=G_MAIN;
	else if(wififlag==2)
		g_sys_state=G_LOGIN;
}
// ��װʵ�ֵ�¼���ܵĺ���
void do_login()
{
	int ts_x,ts_y;
	if(loginflag==0)
		show_login();
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		//�ж��Ƿ���������1
		if(ts_x>230&&ts_x<294&&ts_y>140&&ts_y<204)
			add(1);
		if(ts_x>326&&ts_x<390&&ts_y>140&&ts_y<204)
			add(2);
		if(ts_x>422&&ts_x<486&&ts_y>140&&ts_y<204)
			add(3);
		if(ts_x>230&&ts_x<294&&ts_y>210&&ts_y<274)
			add(4);
		if(ts_x>326&&ts_x<390&&ts_y>210&&ts_y<274)
			add(5);
		if(ts_x>422&&ts_x<486&&ts_y>210&&ts_y<274)
			add(6);
		if(ts_x>230&&ts_x<294&&ts_y>280&&ts_y<344)
			add(7);
		if(ts_x>326&&ts_x<390&&ts_y>280&&ts_y<344)
			add(8);
		if(ts_x>422&&ts_x<486&&ts_y>280&&ts_y<344)
			add(9);
		if(ts_x>230&&ts_x<294&&ts_y>350&&ts_y<414)
			del();
		if(ts_x>326&&ts_x<390&&ts_y>350&&ts_y<414)
			add(0);
		if(ts_x>422&&ts_x<486&&ts_y>350&&ts_y<414)
		{
			enter();
			break;
		}
	}		
}
// ʵ�������湦�ܵĺ���
void do_main()
{
	int ts_x,ts_y;
	show_fullbmp("/wuyi/mainmenu.bmp");
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		// �ж��Ƿ�����������ͷ����
		if(ts_x>10&&ts_x<155&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_CAMERA;
			break;
		}
		// �ж��Ƿ���������Ƶ����
		if(ts_x>315&&ts_x<475&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_VIDEO;
			break;
		}
		// �ж��Ƿ�������ͼƬ����
		if(ts_x>625&&ts_x<768&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_PHOTO;
			break;
		}
		// �ж��Ƿ���������Ϸ����
		if(ts_x>510&&ts_x<647&&ts_y>330&&ts_y<414)
		{
			g_sys_state=G_GAME;
			break;
		}
	}
}
void do_camera()
{
	int ts_x,ts_y;
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		// �ж��Ƿ������Ƿ���
		if(ts_x>640&&ts_x<800&&ts_y>240&&ts_y<480)
		{
			g_sys_state=G_MAIN;
			break;
		}
		// ��ͼƬת������Ƶ
		if(ts_x>640&&ts_x<800&&ts_y>0&&ts_y<240)
		{
			system("ffmpeg -f image2 -i /gec/web/snap/%d.jpg -r 25 /gec/web/video/video.avi\n");
			g_sys_state=G_MAIN;
			break;
		}
	}
}
void *take_photo(void *arg)
{
	// ��α�������ͷ����Ļ���
	FrameBuffer mybuf;
	int jpgnum=0;
	char jpgpath[30];
	int jpgfd;
	while(1)
	{
		// ��ȡ����ͷ����Ļ�������
		linux_v4l2_get_fream(&mybuf); // if-else���õ�һ�����
		// ����������ֻ����ϵͳ����G_CAMERA״̬����������ʾ
		if(g_sys_state==G_CAMERA)
		{
			// ��������lcd����ʾ����
			lcd_draw_jpg(0,0,NULL,mybuf.buf,mybuf.length,0);
		}
		// ϵͳ��������״̬��ʱ���Ҿͱ�������ͷ�����jpg����
		else
		{
			// ����һ���հ׵�jpg�ļ�  ��Ҫ����Ļ���ǳ���
			sprintf(jpgpath,"/gec/web/snap/%d.jpg",jpgnum);
			jpgnum++;
			// �½�������ͬ���ļ�
			jpgfd=open(jpgpath,O_CREAT|O_TRUNC|O_RDWR);
			if(jpgfd==-1)
			{
				printf("create jpgpath failed!\n");
				return NULL;
			}
			// ����ɫֵд�뵽�ÿհ�ͼƬ��
			write(jpgfd,mybuf.buf,mybuf.length);
			close(jpgfd);
		}
	}
}
void do_video()
{
	int ts_x,ts_y;
	/* // ��ʾ��Ƶ���ŵ�������
	show_fullbmp("/wuyi/video.bmp");
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		// �ж��Ƿ������ǲ�����Ƶ����
		if(ts_x>640&&ts_x<800&&ts_y>240&&ts_y<480)
		{
			system("mplayer    ");
		}
		// �ж��Ƿ������Ƿ���
		if(ts_x>640&&ts_x<800&&ts_y>240&&ts_y<480)
		{
			
		}
	} */
}
void do_photo()
{
	
}
void do_game()
{
	
}
void *take_wifi(void *arg)
{
	//��wifi
	wififd=requst_wifi();
	//��ȡwifi��״̬��Ϣ  (���Խ������񽻸��߳�ȥ���)
	if(get_wifi_info(wififd)==ONE_CONNECT)
	{
		if(check_mac()==1)
			wififlag=1;
		else
			wififlag=2;
	}
}
void *take_time(void *arg)
{
	time_t mytime;
	char buf[20];
	int i;
	//
	while(1)
	{
		time(&mytime);
		
		strcpy(buf,ctime(&mytime));
		// ʹ��ctime��ʱ��ת��������ϰ�ߵ��ַ�����ʽ
		printf("����ϵͳʱ���ǣ�%s\n",ctime(&mytime));
		for(i=11;i<19;i++)
		{
			switch(buf[i])
			{
				case '0':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/0..bmp");break;
				case '1':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/1..bmp");break;
				case '2':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/2..bmp");break;
				case '3':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/3..bmp");break;
				case '4':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/4..bmp");break;
				case '5':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/5..bmp");break;
				case '6':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/6..bmp");break;
				case '7':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/7..bmp");break;
				case '8':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/8..bmp");break;
				case '9':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/9..bmp");break;
				case ':':show_anybmp(620+(i-11)*16,30,16,32,"/wuyi/num/:..bmp");break;
				default: break;
			}
		}
		sleep(1);
	}
}
int main()  // ģ��---���޸�С�Ĵ���---����ģ��  ��һ���������ԣ�
{
	
	pthread_t cameraid;
	pthread_t wifiid;
	pthread_t timeid;
	//��ʼ������ͷ
	linux_v4l2_device_init("/dev/video3");
	// ��������ͷ��׽
	linux_v4l2_start_capturing();
	/*//��wifi
	wififd=requst_wifi();
	//��ȡwifi��״̬��Ϣ  (���Խ������񽻸��߳�ȥ���)
	if(get_wifi_info(wififd)==ONE_CONNECT)
	{
		if(check_mac()==1)
			wififlag=1;
		else
			wififlag=2;
	}*/
	//�򿪴�����
	myts_open();
	//�������̣߳�ȥ��������ͷ����ʾ
	pthread_create(&cameraid,NULL,take_photo,NULL);
	pthread_create(&wifiid,NULL,take_wifi,NULL);
	pthread_create(&timeid,NULL,take_time,NULL);
	while(1)
	{
		switch(g_sys_state)  // ʵ���˸�������ģ��֮��Ķ���
		{
			case G_WELCOME:
				do_welcome();  // ʵ�ֻ�ӭ����Ĺ���
				break;
			case G_LOGIN:
				do_login();
				break;
			case G_MAIN:
				do_main();
				break;
			case G_CAMERA:
				do_camera();
				break;
			case G_VIDEO:
				do_video();
				break;
			case G_PHOTO:
				do_photo();
				break;
			case G_GAME:
				do_game();
				break;
		}
	}
	//�ر�wifi
	release_wifi(wififd);
	//�رմ�����
	myts_close();
	return 0;
}