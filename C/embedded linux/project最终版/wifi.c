#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// 由于你使用输入子系统模型中定义的结构体，使用一些特殊的宏定义
#include <linux/input.h>
#define  ONE_CONNECT          1
#define  ONE_DISCONNECT       0
// 封装成一个个独立的函数，然后在main中去调用
// 打开wifi
int requst_wifi()
{
	int wififd;
	// 打开wifi
	wififd=open("/dev/event2",O_RDWR);
	if(wififd==-1)
	{
		printf("open wifi failed!\n");
		return -1;
	}
	return wififd;
}
// 获取wifi的连接状态
int get_wifi_info(int fd)
{
	struct input_event mywifi;
	// 读取wifi的状态信息
	read(fd,&mywifi,sizeof(struct input_event));
	// 分析判断读取到的信息 type---》EV_KEY  code   value
	// 判断输入事件是不是wifi引起的
	if(mywifi.type==EV_KEY)
	{
		// 判断是否有手机连入
		if(mywifi.code==BTN_0&&mywifi.value==1)
			return ONE_CONNECT;  // 返回值是1表示有手机连入
		else if(mywifi.code==BTN_1&&mywifi.value==1)
			return ONE_DISCONNECT;
	}
	return 2;
}
// 判断连入的手机是不是绑定的合法手机
int check_mac()
{
	int bindfd;
	int linkfd;
	int ret;
	char bindbuf[18];
	char linkbuf[18];
	// 打开系统中绑定合法手机地址的那个文件
	bindfd=open("/usr/Bind_addr",O_RDWR);
	if(bindfd==-1)
	{
		printf("open bind file faied!\n");
		return -1;
	}
	// 打开存放连入手机MAC的文件
	linkfd=open("/sys/module/rt3070ap/parameters/Mac_addr",O_RDONLY);  // 只能用只读方式打开
	if(linkfd==-1)
	{
		printf("open link file faied!\n");
		return -1;
	}
	lseek(bindfd,0,SEEK_SET);
	// 读取绑定的那个MAC地址
	read(bindfd,bindbuf,18);
	lseek(linkfd,0,SEEK_SET);
	// 读取连入wifi的手机MAC地址
	read(linkfd,linkbuf,18);
	// 比对两个地址是否一样
	// "lkjfjhsdfh"   "zbc"
	if(strncmp(bindbuf,linkbuf,18)==0)
		ret=1;
	else
		ret=0;
	return ret;
}
// wifi的关闭
int release_wifi(int fd)
{
	close(fd);
	return 0;
}