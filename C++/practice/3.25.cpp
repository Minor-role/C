#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<unsigned> scores(11,0);
	int grade;
	auto value = scores.begin();
	while(cin >> grade)
	{
		if(grade <= 100)
			(*(value + grade/10)) ++;
	}
	for (auto x : scores)
		cout << x << " ";
	system("pause");
	return 0;
}
