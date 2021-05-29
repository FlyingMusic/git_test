/*
 * 实现分析：
 * 如果不考虑性能,用vector就可以实现,但考虑到要保证顺序,所以会涉及到很多“把中间元素拿到后面”的操作
 * 所以主要容器考虑用list实现，但list对于"判断容器中是否存在该元素"比较费时，这种是map/unordered_map
 * 的专长，所以用list+unordered_map实现，为快速确认list中结点位置，map中存放list结点的指针
 *
 * 最佳实践：
 * 1. map里放list的指针，二者组成一个容器，可以既有map的优势又有list的优势
 * 2. 注意模板类里各种复杂类型可以使用typedef来简化，有些类型需要加typename来告诉编译器这是一种类型
 *
 * */

#include <list>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

template<typename Key, typename Value>
class LRUCache 
{
public:
    LRUCache(int cap = 10) : capacity(cap) { }
    void set(Key key, Value value);
    Value get(Key key);
        
private:
    int capacity;
    typedef list<pair<Key, Value>> List;
    typedef typename list<pair<Key, Value>>::iterator ListIter;
    typedef unordered_map<Key, ListIter> Map;
    typedef typename unordered_map<Key, ListIter>::iterator MapIter;
    
    List m_list;
    Map m_map;
};

template<typename Key, typename Value>
void LRUCache<Key, Value>::set(Key key, Value value) {
    MapIter miter = m_map.find(key);
    if(miter != m_map.end()) { //已经存在
        ListIter liter = miter->second;
        m_list.erase(liter);
    }
    m_list.push_front(make_pair(key, value));
    m_map[key] = m_list.begin();
    if(m_map.size() > capacity) {
       m_map.erase(m_list.rbegin()->first); 
       m_list.pop_back();
    }
}

template<typename Key, typename Value>
Value LRUCache<Key, Value>::get(Key key) {
    MapIter miter = m_map.find(key);
    if(miter != m_map.end()) {
        ListIter liter = miter->second;        
        m_list.splice(m_list.begin(), m_list, liter);
        return liter->second; 
    }
    return Value();
}
int main() {
    LRUCache<int, string> lru(5);
    lru.set(1, "one");
    lru.set(2, "two");
    lru.set(3, "three");
    lru.set(4, "fore");
    lru.set(5, "five");
    lru.set(1, "one");
    lru.set(6, "six");
    cout << lru.get(1) << endl;
    cout << lru.get(2) << endl;
    cout << lru.get(3) << endl;
    cout << lru.get(4) << endl;
    cout << lru.get(5) << endl;
    cout << lru.get(6) << endl;
    cout << lru.get(7) << endl;
    return 0;
}
