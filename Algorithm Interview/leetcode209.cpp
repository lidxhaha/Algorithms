class Solution {
public:
   //滑动窗口法
   // 很酷
    int minSubArrayLen(int s, vector<int>& nums) {
        int l = 0, r = -1; // [l,r]为滑动窗口，初始时滑动窗口什么都没有
        int sum = 0;
        int res = nums.size() + 1;
        
        while(l < nums.size()){
            if (r+1 < nums.size() && sum < s)
                sum += nums[++r];
            else
                sum -= nums[l++];
            if (sum >= s)
                res = min(res, r-l+1);
        }
     
        if (res == nums.size() + 1)
            return 0;
        return res;
    }
};