/*
  该文件存放了所有关于bmp格式图片显示的函数
  版权：xxxxx
  版本：
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/mman.h>
// 封装一个专门用于显示800*480bmp格式图片的函数
int show_fullbmp(char *bmpname)
{
	int bmpfd;
	int lcdfd;
	int i;
	int x,y;
	// 定义数组用于存放图片的颜色值
	char bmpbuf[800*480*3];  //char 占一字节
	// 定义数组存放转换后的4字节的数据
	int lcdbuf[800*480]; // int占4个字节
	int tembuf[800*480];
	//打开你要显示的bmp格式图片  800*480
	bmpfd=open(bmpname,O_RDWR);
	//错误的判断
	if(bmpfd==-1)
	{
		printf("open %s failed!\n",bmpname);
		return -1;
	}
	//打开LCD
	lcdfd=open("/dev/fb0",O_RDWR);
	//错误的判断
	if(lcdfd==-1)
	{
		printf("open LCD failed!\n");
		return -1;
	}
	// 在读之前跳过前面54字节的头信息
	lseek(bmpfd,54,SEEK_SET);
	// 从55字节的位置读出bmp图片的颜色值 800*480*3字节
	read(bmpfd,bmpbuf,800*480*3);
	// 将读到的颜色3字节---》4字节
	for(i=0; i<800*480; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;
	// 00[2][1][0]
	// 将颠倒的图像翻转过来
	for(x=0; x<800; x++)
		for(y=0; y<480; y++) //for循环的嵌套，保证将图片每个坐标位置全部都过一遍
			tembuf[(479-y)*800+x]=lcdbuf[y*800+x];
	// 将转换之后的数据写入到LCD中
	write(lcdfd,tembuf,800*480*4);
	// 关闭
	close(bmpfd);
	close(lcdfd);
	return 0;
}
// 封装一个专门用于显示任意大小bmp格式图片的函数
int show_anybmp(int x,int y,int w,int h,char *bmpname)
{
	int bmpfd;
	int lcdfd;
	int *lcdmem;
	int i;
	int j;
	// 定义数组用于存放图片的颜色值
	char bmpbuf[w*h*3];  //char 占一字节
	// 定义数组存放转换后的4字节的数据
	int lcdbuf[w*h]; // int占4个字节
	int tembuf[w*h];
	//打开你要显示的bmp格式图片  w*h
	bmpfd=open(bmpname,O_RDWR);
	//错误的判断
	if(bmpfd==-1)
	{
		printf("open %s failed!\n",bmpname);
		return -1;
	}
	//打开LCD
	lcdfd=open("/dev/fb0",O_RDWR);
	//错误的判断
	if(lcdfd==-1)
	{
		printf("open LCD failed!\n");
		return -1;
	}
	//映射lcd
	lcdmem=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	// 在读之前跳过前面54字节的头信息
	lseek(bmpfd,54,SEEK_SET);
	// 从55字节的位置读出bmp图片的颜色值 800*480*3字节
	read(bmpfd,bmpbuf,w*h*3);
	// 将读到的颜色3字节---》4字节
	for(i=0; i<w*h; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;
	// 00[2][1][0]
	// 将图片上(i,j)--->lcd上（x+i,y+j）  颠倒的
	// 将图片上(i,h-1-j)--->lcd上（x+i,y+j）  正常的
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			*(lcdmem+(y+j)*800+x+i)=lcdbuf[(h-1-j)*w+i];
	// 关闭
	close(bmpfd);
	close(lcdfd);
	// 解除映射
	munmap(lcdmem,800*480*4);
	return 0;
}

