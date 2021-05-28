#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution1 {
    static bool myCompare(string x, string y) {//降序
        return x + y > y + x;

    }
    static bool mc(string x, string y) {
        return (x + y).compare(y + x);
    }
    public:
    static string largestNumber(vector<int>& nums) {

        vector<string> numStr;
        string max;
        for (auto iter = nums.begin(); iter != nums.end(); iter++)
            numStr.push_back(to_string(*iter));
        sort(numStr.begin(), numStr.end(), myCompare);//这里报错了！！！！！
        for (auto a : numStr) {
            max += a;
        }
        if (max[0] == '0')return "0";
        return max;

    }

};

int main()
{
    vector<int> numStr;
    numStr.push_back(321);
    numStr.push_back(123);
    cout << Solution1::largestNumber(numStr) << endl;
    map<int[2], int> txt; 
    return 0;
}
