#include <iostream>

using namespace std;

int main()
{
	int *p = new int[2];
	p[1] = 5;
	cout << p[1] << endl;
	delete[] p;
	int a[2] = {0};
	a[2] = 3;
	cout << a[2] << endl;
	return 0;
}
