// 一道求数组中目标数上确界和下确界的题目
// input: nums = [5,7,7,8,8,10], target = 8
// output: [3, 4]

#include <vector>

class Solution {
public:
    vector<int> serarchRange(vector<int>& nums, int target) {
        // 找目标数的下确界
        int index1 = findTarget(nums, target);
        // 小tricky，找目标数+1的下确界然后再减一，就是目标数的上确界
        int index2 = findTarget(nums, target + 1) - 1;
        // 错误处理，如果数组中没有目标数，返回{-1，-1}
        if (index1 < nums.size() && nums[index1] == target) { 
            return {index1, index2}
        }
        else{
            return {-1, -1}
        }
    }

    // 找下确界，二分法，注意搜索范围，循环终止条件
    int findTarget(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;    
    // 这里就定义了搜索区间是[left, right],循环终止条件是left > right，也就是说搜索区间变为[right + 1, right]，
    // 这个区间确实不能搜索了，如果是left < right，循环终止条件变为left >= right，
    // 搜索区间中的[right, right]就没被处理到 
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                right = mid - 1;                 //找下确界，不断往左逼近
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        return left;             
    }
}；