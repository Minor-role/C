#include <iostream>
#include <string>
#include <windows.h>
int main(int argc, char const *argv[])
{
	using std::cin;
	using std::cout;
	using std::string;
	string s1,s2;
	cin >> s1 >> s2;
	if (s1 > s2)
		cout<< s1 << std::endl;
	else
		cout<< s2 << std::endl;
	system("pause");
	return 0;
}