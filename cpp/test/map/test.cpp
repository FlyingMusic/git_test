#include <map>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    map<int, string> int_string_map;
    if(int_string_map[1] != NULL) {
        cout << "map is NULL"<< endl;
    }
    cout << int_string_map[1] << endl;
    return 0;
}
