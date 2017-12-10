#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
	int x,y;
	int sum = 0;
	cin >> x >> y;
	while(x <= y)
	{
		sum += x;
		x++;
	}
	cout << sum << endl;
	return 0;
}
