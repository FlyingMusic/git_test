#include <stack>
#include <iostream>
#include <map>
#include <unordered_map>
#include <functional>

using namespace std;

template<typename Type>
class FreqStack {
public:
    void push(Type elem);
    Type top();
    void pop();
private:
    typedef stack<Type> Stack;
    typedef map<int, Stack, greater<int>> Map;
    typedef typename Map::iterator MapIter;
    typedef unordered_map<Type, int> UMap;
    typedef typename UMap::iterator UMapIter;

    Map m_map;
    UMap m_umap;
};

template<typename Type>
void FreqStack<Type>::push(Type elem) {
    if(m_umap.find(elem) != m_umap.end()) {
        m_umap[elem]++;
    } else {
        m_umap[elem] = 1;
    }
    m_map[m_umap[elem]].push(elem);
}

template<typename Type>
Type FreqStack<Type>::top() {
    MapIter miter = m_map.begin();
    if(miter != m_map.end())
        return miter->second.top();
    else
        return Type();
}

template<typename Type>
void FreqStack<Type>::pop() {
    MapIter miter = m_map.begin();
    if(miter != m_map.end()) {
        Type elem = top();
        m_umap[elem]--;
        miter->second.pop();
        if(miter->second.size() == 0) 
            m_map.erase(miter);
    }
}

int main() {
    FreqStack<int> fstack;
    fstack.push(5);
    fstack.push(7);
    fstack.push(5);
    fstack.push(7);
    fstack.push(4);
    fstack.push(5);
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    cout << fstack.top() << endl; fstack.pop();
    return 0;
}
