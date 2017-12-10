#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> s;
	int word,size,sum;
	char cont = 'y';
	while(cin >> word)
	{
		s.push_back(word);
		cout << "Enter again? (Y/N)" << endl;
		cin >> cont;
		if (cont != 'y' && cont !='Y')
			break;
	}
	size = s.size();
	for(int i = 0, j = size-1;j > size/2 ;i++,j--)
	{
		sum = s[i] + s[j];
		cout << sum << " ";
	}
	if(size % 2 != 0)
		cout << s[size/2] << " ";
	cout << endl;
	system("pause");
	return 0;
}
