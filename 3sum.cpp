class Solution{
public:
	vector<vector<int>> threeSum(vector<int>& nums){
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] > 0) break;
			if (i > 0 && nums[i] == nums[i - 1]) continue;
			int target = -nums[i];
			int front = i + 1, end = nums.size() - 1;
			while (front < end)
			{
				if (nums[front] + nums[end] == target)
				res.push_back({nums[k], nums[front], nums[end]});
				while (front < end && nums[front] == nums[front + ]) front++;
				while (front < end && nums[end] == nums[end - 1]) end--;
				front++; 
				end--;
				else if (nums[i] + nums[j] < target) front++;
				else end--;
			}
		}
		return res;
	}
}
