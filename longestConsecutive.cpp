#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        vector<vector<int>> lists;
        for(int i = 0; i < nums.size(); i++) {
            if(lists.empty()) {
                vector<int> temp;
                temp.push_back(nums[i]);
                lists.push_back(temp);
                continue;
            }
            bool flag = false;
            for(int j = 0; j < lists.size(); j++) {
                if(nums[i] == lists[j].size() + 1) {
                    lists[j].push_back(nums[i]);
                    flag = true;
                    break;
                }
            }
            if(flag == false) {
                vector<int> temp;
                temp.push_back(nums[i]);
                lists.push_back(temp);
                continue;
            }
        }
        int max = -1;
        for(int i = 0; i < lists.size(); i++) {
            if(max < lists[i].size())
                max = lists[i].size();
        }
        for(int i = 0; i < lists.size(); i++) {
            for(int j = 0;j<lists[i].size();j++){
                cout << lists[i][j] << " ";
            }
        }
        return max;
    }
};

int main() {
    Solution sol;
    vector<int> nums;
    int x;
    cout << "请输入一组整数（空格分隔，回车结束）:" << endl;
    while (cin >> x) {
        nums.push_back(x);
        if (cin.get() == '\n') break;
    }
    int res = sol.longestConsecutive(nums);
    cout << res << endl;
    return 0;
}