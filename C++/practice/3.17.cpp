#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<string> s;
	string word;
	char cont = 'y';
	while(cin >> word)
	{
		s.push_back(word);
		cout << "Enter again? (Y/N)" << endl;
		cin >> cont;
		if (cont != 'y' && cont !='Y')
			break;
	}
	for(auto w : s)
	{
		for(auto &l : w)
			l = toupper(l);
		cout << w << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}