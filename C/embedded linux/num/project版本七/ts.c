#include <stdio.h>
// ���ڴ�����Ҫʹ��tslib.h�������Ľӿں���
#include "tslib.h"
struct tsdev *myts;
// ��װһ���������򿪵ĺ���
int myts_open()
{
	// �򿪴�����
	myts=ts_open("/dev/event0",0);
	if(myts==NULL)
	{
		printf("open ts failed!\n");
		return -1;
	}
	// ���ô�����
	ts_config(myts);
	return 0;
}
// ��ȡx��y����
int get_x_y(int *x,int *y)
{
	struct ts_sample mysample;
	while(1)
	{
		// ��ȡ���������ص�x��y����
		ts_read(myts,&mysample,1);
		*x=mysample.x;
		*y=mysample.y;
		if(mysample.pressure==0)
			break;
	}
	return 0;
}
// �������Ĺر�
int myts_close()
{
	ts_close(myts);
	return 0;
}
