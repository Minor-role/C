#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<string> s;
	string word;
	while(getline(cin,word))
		s.push_back(word);
	for(auto w = s.begin(); w != s.end(); ++w)
	{
		for(auto l = w->begin(); l != w->end(); ++l)
			*l = toupper(*l);
		cout << (*w) << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}