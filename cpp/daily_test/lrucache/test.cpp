#include <list>
#include <unordered_map>

using namespace std;

template<typename Type>
class A 
{
    list<Type> lst;
    unordered_map<Type, list<Type>> m1; //OK
    unordered_map<Type, list<Type>::iterator > m2; //ERROR
    unordered_map<Type, list<int>::iterator> m3; //OK
    
};

int main() {
    return 0;
}
