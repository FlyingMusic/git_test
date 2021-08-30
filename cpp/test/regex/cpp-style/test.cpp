#include <regex>
#include <iostream>

using namespace std;


int main() {
    cout << regex_match("<tag>value</tag>", regex("<(.*)>.*</\\1>")) << endl;
    return 0;
}
    

