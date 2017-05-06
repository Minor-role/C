/*
  ���ļ���������й���bmp��ʽͼƬ��ʾ�ĺ���
  ��Ȩ��xxxxx
  �汾��
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/mman.h>
// ��װһ��ר��������ʾ800*480bmp��ʽͼƬ�ĺ���
int show_fullbmp(char *bmpname)
{
	int bmpfd;
	int lcdfd;
	int i;
	int x,y;
	// �����������ڴ��ͼƬ����ɫֵ
	char bmpbuf[800*480*3];  //char ռһ�ֽ�
	// ����������ת�����4�ֽڵ�����
	int lcdbuf[800*480]; // intռ4���ֽ�
	int tembuf[800*480];
	//����Ҫ��ʾ��bmp��ʽͼƬ  800*480
	bmpfd=open(bmpname,O_RDWR);
	//������ж�
	if(bmpfd==-1)
	{
		printf("open %s failed!\n",bmpname);
		return -1;
	}
	//��LCD
	lcdfd=open("/dev/fb0",O_RDWR);
	//������ж�
	if(lcdfd==-1)
	{
		printf("open LCD failed!\n");
		return -1;
	}
	// �ڶ�֮ǰ����ǰ��54�ֽڵ�ͷ��Ϣ
	lseek(bmpfd,54,SEEK_SET);
	// ��55�ֽڵ�λ�ö���bmpͼƬ����ɫֵ 800*480*3�ֽ�
	read(bmpfd,bmpbuf,800*480*3);
	// ����������ɫ3�ֽ�---��4�ֽ�
	for(i=0; i<800*480; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;
	// 00[2][1][0]
	// ���ߵ���ͼ��ת����
	for(x=0; x<800; x++)
		for(y=0; y<480; y++) //forѭ����Ƕ�ף���֤��ͼƬÿ������λ��ȫ������һ��
			tembuf[(479-y)*800+x]=lcdbuf[y*800+x];
	// ��ת��֮�������д�뵽LCD��
	write(lcdfd,tembuf,800*480*4);
	// �ر�
	close(bmpfd);
	close(lcdfd);
	return 0;
}
// ��װһ��ר��������ʾ�����Сbmp��ʽͼƬ�ĺ���
int show_anybmp(int x,int y,int w,int h,char *bmpname)
{
	int bmpfd;
	int lcdfd;
	int *lcdmem;
	int i;
	int j;
	// �����������ڴ��ͼƬ����ɫֵ
	char bmpbuf[w*h*3];  //char ռһ�ֽ�
	// ����������ת�����4�ֽڵ�����
	int lcdbuf[w*h]; // intռ4���ֽ�
	int tembuf[w*h];
	//����Ҫ��ʾ��bmp��ʽͼƬ  w*h
	bmpfd=open(bmpname,O_RDWR);
	//������ж�
	if(bmpfd==-1)
	{
		printf("open %s failed!\n",bmpname);
		return -1;
	}
	//��LCD
	lcdfd=open("/dev/fb0",O_RDWR);
	//������ж�
	if(lcdfd==-1)
	{
		printf("open LCD failed!\n");
		return -1;
	}
	//ӳ��lcd
	lcdmem=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	// �ڶ�֮ǰ����ǰ��54�ֽڵ�ͷ��Ϣ
	lseek(bmpfd,54,SEEK_SET);
	// ��55�ֽڵ�λ�ö���bmpͼƬ����ɫֵ 800*480*3�ֽ�
	read(bmpfd,bmpbuf,w*h*3);
	// ����������ɫ3�ֽ�---��4�ֽ�
	for(i=0; i<w*h; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;
	// 00[2][1][0]
	// ��ͼƬ��(i,j)--->lcd�ϣ�x+i,y+j��  �ߵ���
	// ��ͼƬ��(i,h-1-j)--->lcd�ϣ�x+i,y+j��  ������
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			*(lcdmem+(y+j)*800+x+i)=lcdbuf[(h-1-j)*w+i];
	// �ر�
	close(bmpfd);
	close(lcdfd);
	// ���ӳ��
	munmap(lcdmem,800*480*4);
	return 0;
}

