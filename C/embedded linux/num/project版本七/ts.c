#include <stdio.h>
// 由于代码中要使用tslib.h中声明的接口函数
#include "tslib.h"
struct tsdev *myts;
// 封装一个触摸屏打开的函数
int myts_open()
{
	// 打开触摸屏
	myts=ts_open("/dev/event0",0);
	if(myts==NULL)
	{
		printf("open ts failed!\n");
		return -1;
	}
	// 配置触摸屏
	ts_config(myts);
	return 0;
}
// 获取x，y坐标
int get_x_y(int *x,int *y)
{
	struct ts_sample mysample;
	while(1)
	{
		// 读取触摸屏返回的x，y坐标
		ts_read(myts,&mysample,1);
		*x=mysample.x;
		*y=mysample.y;
		if(mysample.pressure==0)
			break;
	}
	return 0;
}
// 触摸屏的关闭
int myts_close()
{
	ts_close(myts);
	return 0;
}
