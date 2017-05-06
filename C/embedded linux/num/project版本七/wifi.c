#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// ������ʹ��������ϵͳģ���ж���Ľṹ�壬ʹ��һЩ����ĺ궨��
#include <linux/input.h>
#define  ONE_CONNECT          1
#define  ONE_DISCONNECT       0
// ��װ��һ���������ĺ�����Ȼ����main��ȥ����
// ��wifi
int requst_wifi()
{
	int wififd;
	// ��wifi
	wififd=open("/dev/event2",O_RDWR);
	if(wififd==-1)
	{
		printf("open wifi failed!\n");
		return -1;
	}
	return wififd;
}
// ��ȡwifi������״̬
int get_wifi_info(int fd)
{
	struct input_event mywifi;
	// ��ȡwifi��״̬��Ϣ
	read(fd,&mywifi,sizeof(struct input_event));
	// �����ж϶�ȡ������Ϣ type---��EV_KEY  code   value
	// �ж������¼��ǲ���wifi�����
	if(mywifi.type==EV_KEY)
	{
		// �ж��Ƿ����ֻ�����
		if(mywifi.code==BTN_0&&mywifi.value==1)
			return ONE_CONNECT;  // ����ֵ��1��ʾ���ֻ�����
		else if(mywifi.code==BTN_1&&mywifi.value==1)
			return ONE_DISCONNECT;
	}
	return 2;
}
// �ж�������ֻ��ǲ��ǰ󶨵ĺϷ��ֻ�
int check_mac()
{
	int bindfd;
	int linkfd;
	int ret;
	char bindbuf[18];
	char linkbuf[18];
	// ��ϵͳ�а󶨺Ϸ��ֻ���ַ���Ǹ��ļ�
	bindfd=open("/usr/Bind_addr",O_RDWR);
	if(bindfd==-1)
	{
		printf("open bind file faied!\n");
		return -1;
	}
	// �򿪴�������ֻ�MAC���ļ�
	linkfd=open("/sys/module/rt3070ap/parameters/Mac_addr",O_RDONLY);  // ֻ����ֻ����ʽ��
	if(linkfd==-1)
	{
		printf("open link file faied!\n");
		return -1;
	}
	lseek(bindfd,0,SEEK_SET);
	// ��ȡ�󶨵��Ǹ�MAC��ַ
	read(bindfd,bindbuf,18);
	lseek(linkfd,0,SEEK_SET);
	// ��ȡ����wifi���ֻ�MAC��ַ
	read(linkfd,linkbuf,18);
	// �ȶ�������ַ�Ƿ�һ��
	// "lkjfjhsdfh"   "zbc"
	if(strncmp(bindbuf,linkbuf,18)==0)
		ret=1;
	else
		ret=0;
	return ret;
}
// wifi�Ĺر�
int release_wifi(int fd)
{
	close(fd);
	return 0;
}