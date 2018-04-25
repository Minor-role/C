/*
create by Ian in 2018-1-1 20:55:48
汽车加油问题：贪心算法

题目描述：
	i：加油站序号，第一个加油站为0号
	x：距离
	x[i]：从上一个加油站到当前加油站的距离
	n：车满油行驶路程
	k：加油站数
	go：已走路程
	freq：停加油站次数
	j：汽车所在加油站序号
	count：总路程
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int n, k, x[20],count = 0; // 车可行驶公里数，加油站数，起点终点加油站间距离， 总距离
	cin >> n >> k;
	for (int j = 0; j<k; j++)x[j] = 0;
	for (int i = 0; i<=k; i++)
	{
		cin >> x[i];
		count += x[i];
	}
	int i = 0,go = 0, freq = 0; // 加油站序号，已走路程，保存加油站序号，需停留次数
	int j, sgo;
	while(go < count)
	{
		for(j = i, sgo = 0; j<= k-1 && sgo + x[j] <= n; j++)
		{
			sgo += x[j];
		}
		cout << "序号：" << j << " ";
		i = j;
		go += sgo;
		++freq;
		if(go + n >= count)break; // 如果不需要加油也能走完，就直接跳出
	}
	cout << endl <<freq;
	return 0;
}

