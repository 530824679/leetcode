/*
找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
说明：
    所有数字都是正整数。
    解集不能包含重复的组合。
示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]

示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// 方法一：二进制（子集）枚举
class Solution1{
public:
    bool checksum(int mask, int k, int n) {
        tmp_.clear();
        for(int i = 0; i < 9; i++){
            if((1<<i) & mask)
                tmp_.push_back(i+1);
        }
        return tmp_.size() == k && accumulate(tmp_.begin(), tmp_.end(), 0) == n;
    }

    vector<vector<int>> combinationSum3(int k, int n) {

        for (int mask = 0; mask < (1 << 9); mask++) {
            if (checksum(mask, k, n)){
                result_.push_back(tmp_);
            }
        }
        return result_;
    }

private:
    vector<vector<int>> result_;
    vector<int> tmp_;

};

// 方法二：回溯算法
// 解集不能包含重复的组合。 说明不用去重了，难度就小一些。
// 求的是组合，那么集合没有顺序，for里面依然要从startIndex开始（如果是排列的话，就从0开始）
// k限制了树的深度，9就是树的宽度

/*
   backtracking() {
    if (终止条件) {
        存放结果;
    }

    for (选择：选择列表（可以想成树中节点孩子的数量）) {
        递归，处理节点;
        backtracking();
        回溯，撤销处理结果
    }
}
*/

class Solution2{
private:
    vector<vector<int>> result;
    vector<int> tmp;
    void backtracking(int target, int k, int num, int sum, int startIndex){
        if(sum > target || num > k)
            return;

        if(sum == target && num == k){
            result.push_back(tmp);
            return;
        }

        for (int i = startIndex; i <= 9; i++) {
            sum += i;
            tmp.push_back(i);
            num ++;
            backtracking(target, k, num, sum, i+1);
            sum -= i;
            num --;
            tmp.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(n, k, 0, 0, 1);
        return result;

    }

};

int main() {
    Solution2 sl;
    vector<vector<int>> result = sl.combinationSum3(3, 7);
    for (int i = 0; i < result.size(); ++i) {
        vector<int> cell = result[i];
        for (int j = 0; j < cell.size(); ++j) {
            cout << cell[j] << " ";
        }
        cout << endl;
    }
    return 0;
}