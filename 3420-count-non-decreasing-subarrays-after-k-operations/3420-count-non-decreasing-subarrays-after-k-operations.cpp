class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        deque<pair<int, int>> dq;

        long long ans = 0;
        long long cost = 0;

        int j = nums.size() - 1;

        for (int i = nums.size() - 1; i >= 0; i--) {
            int count = 1;
            while (!dq.empty() && dq.back().first < nums[i]) {
                auto [val, cnt] = dq.back();
                dq.pop_back();

                count += cnt;
                cost += 1LL * (nums[i] - val) * cnt;
            }

            dq.push_back({nums[i], count});
            while (cost > k) {
                auto [val, cnt] = dq.front();
                dq.pop_front();

                cost -= val - nums[j];
                j--;

                if (cnt > 1) {
                    dq.push_front({val, cnt - 1});
                }
            }
            ans += j - i + 1;
        }
        return ans;
    }
};
