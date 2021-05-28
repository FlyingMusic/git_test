#include <iostream>

using namespace std;

int main()
{
#ifdef _DPRINT
	cout << "hello macro" << endl;
#endif
	return 0;
}
