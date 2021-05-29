#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

pair<int, int> twoSum(int *arr, int alen, int sum) {
    unordered_map<int, int> map;
    for(int i = 0; i < alen; ++i) {
        unordered_map<int, int>::iterator iter = map.find(sum-arr[i]);
        if(iter == map.end()) {
            map[arr[i]] = i;
        } else {
            return make_pair(iter->second, i); 
        }
    } 
    return make_pair(-1, -1);
}

int main() {
    int sum = 0;
    cin >> sum;
    int arr[] = {2, 4, 1, 6, 4, 5, 6, 7, 1};
    pair<int, int> pr = twoSum(arr, sizeof(arr)/sizeof(*arr), sum);
    cout << pr.first << " " << pr.second << endl;
    cout << arr[pr.first] << " " << arr[pr.second] << endl;
    return 0;
}

