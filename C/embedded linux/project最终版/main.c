#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
// 由于要使用摄像头的接口函数
#include "api_v4l2.h"

#define  ONE_CONNECT          1
#define  ONE_DISCONNECT       0
// 使用宏定义去定义系统的几种状态
// 扩展性很强
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
// 定义一个变量记录密码的偏移
int g_off_t=0;
// 定义一个变量记录系统的状态
int g_sys_state=1;
// 定义一个字符类型的数组存放密码
char password[6];
// 定义一个二维数组存放图片的路径
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
// 显示登录界面的函数
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
// 显示你点击的数字密码
int add(int n)  //  n是2
{
	if(g_off_t<6)
	{
		// 显示点击的数字密码
		show_anybmp(265+g_off_t*64,75,64,64,bmppath[n]);
		// 延时
		usleep(50000);
		show_anybmp(265+g_off_t*64,75,64,64,"/wuyi/num/xing.bmp");//遮挡密码
		
		// 将你点击的数字密码保存起来
		password[g_off_t]=n+'0';   // 整数n变成字符'n'
		g_off_t++; 
	}
}
// 
int del()
{
	if(g_off_t>0)
	{
		//障眼法
		show_anybmp(265+(g_off_t-1)*64,75,64,64,"/wuyi/num/black.bmp");
		//清除数组中错误的密码
		password[g_off_t-1]='\0';
		g_off_t--;
	}
}
int enter()
{
	int fd;
	char buf[6];
	// 打开系统中存放正确密码的文档
	fd=open("/wuyi/passwd.txt",O_RDWR);
	if(fd==-1)
	{
		printf("open passwd.txt failed!\n");
		return -1;
	}
	// 读取里面存放的正确密码
	read(fd,buf,6);
	close(fd);
	// 对比密码
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
// 封装实现欢迎界面功能的函数
void do_welcome()
{
	//显示欢迎界面
	show_fullbmp("/wuyi/welcome.bmp");
	//修改系统的状态
	if(wififlag==1)
		g_sys_state=G_MAIN;
	else if(wififlag==2)
		g_sys_state=G_LOGIN;
}
// 封装实现登录功能的函数
void do_login()
{
	int ts_x,ts_y;
	if(loginflag==0)
		show_login();
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		//判断是否点击的数字1
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
// 实现主界面功能的函数
void do_main()
{
	int ts_x,ts_y;
	show_fullbmp("/wuyi/mainmenu.bmp");
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		// 判断是否点击的是摄像头功能
		if(ts_x>10&&ts_x<155&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_CAMERA;
			break;
		}
		// 判断是否点击的是视频功能
		if(ts_x>315&&ts_x<475&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_VIDEO;
			break;
		}
		// 判断是否点击的是图片功能
		if(ts_x>625&&ts_x<768&&ts_y>130&&ts_y<220)
		{
			g_sys_state=G_PHOTO;
			break;
		}
		// 判断是否点击的是游戏功能
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
		// 判断是否点击的是返回
		if(ts_x>640&&ts_x<800&&ts_y>240&&ts_y<480)
		{
			g_sys_state=G_MAIN;
			break;
		}
		// 将图片转换成视频
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
	// 如何保存摄像头拍摄的画面
	FrameBuffer mybuf;
	int jpgnum=0;
	char jpgpath[30];
	int jpgfd;
	while(1)
	{
		// 获取摄像头拍摄的画面数据
		linux_v4l2_get_fream(&mybuf); // if-else共用的一句代码
		// 限制条件，只能是系统处于G_CAMERA状态才能拍摄显示
		if(g_sys_state==G_CAMERA)
		{
			// 将画面在lcd上显示出来
			lcd_draw_jpg(0,0,NULL,mybuf.buf,mybuf.length,0);
		}
		// 系统处于其他状态的时候我就保存摄像头拍摄的jpg画面
		else
		{
			// 创建一个空白的jpg文件  我要保存的画面非常多
			sprintf(jpgpath,"/gec/web/snap/%d.jpg",jpgnum);
			jpgnum++;
			// 新建并覆盖同名文件
			jpgfd=open(jpgpath,O_CREAT|O_TRUNC|O_RDWR);
			if(jpgfd==-1)
			{
				printf("create jpgpath failed!\n");
				return NULL;
			}
			// 将颜色值写入到该空白图片中
			write(jpgfd,mybuf.buf,mybuf.length);
			close(jpgfd);
		}
	}
}
void do_video()
{
	int ts_x,ts_y;
	/* // 显示视频播放的主界面
	show_fullbmp("/wuyi/video.bmp");
	while(1)
	{
		get_x_y(&ts_x,&ts_y);
		// 判断是否点击的是播放视频功能
		if(ts_x>640&&ts_x<800&&ts_y>240&&ts_y<480)
		{
			system("mplayer    ");
		}
		// 判断是否点击的是返回
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
	//打开wifi
	wififd=requst_wifi();
	//获取wifi的状态信息  (可以将该任务交给线程去完成)
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
		// 使用ctime将时间转换成人类习惯的字符串形式
		printf("现在系统时间是：%s\n",ctime(&mytime));
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
int main()  // 模仿---》修改小的创新---》再模仿  举一反三（悟性）
{
	
	pthread_t cameraid;
	pthread_t wifiid;
	pthread_t timeid;
	//初始化摄像头
	linux_v4l2_device_init("/dev/video3");
	// 启动摄像头捕捉
	linux_v4l2_start_capturing();
	/*//打开wifi
	wififd=requst_wifi();
	//获取wifi的状态信息  (可以将该任务交给线程去完成)
	if(get_wifi_info(wififd)==ONE_CONNECT)
	{
		if(check_mac()==1)
			wififlag=1;
		else
			wififlag=2;
	}*/
	//打开触摸屏
	myts_open();
	//创建好线程，去处理摄像头的显示
	pthread_create(&cameraid,NULL,take_photo,NULL);
	pthread_create(&wifiid,NULL,take_wifi,NULL);
	pthread_create(&timeid,NULL,take_time,NULL);
	while(1)
	{
		switch(g_sys_state)  // 实现了各个功能模块之间的独立
		{
			case G_WELCOME:
				do_welcome();  // 实现欢迎界面的功能
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
	//关闭wifi
	release_wifi(wififd);
	//关闭触摸屏
	myts_close();
	return 0;
}