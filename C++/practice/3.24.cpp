#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> s;
	int word,sum;
	char cont = 'y';
	while(cin >> word)
	{
		s.push_back(word);
		cout << "Enter again? (Y/N)" << endl;
		cin >> cont;
		if (cont != 'y' && cont !='Y')
			break;
	}
	auto beg = s.cbegin(),end = s.cend() - 1; 
	for(;beg < end;++beg,--end)
	{
		sum = (*beg) + (*end);
		cout << sum << " ";
	}
	if (s.size() % 2 != 0)
		cout << s[s.size()/2];
	cout << endl;
	system("pause");
	return 0;
}
