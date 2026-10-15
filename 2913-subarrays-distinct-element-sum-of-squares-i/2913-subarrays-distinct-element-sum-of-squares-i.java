import java.util.HashSet;
import java.util.Set;
import java.util.List;
class Solution {
    public int sumCounts(List<Integer> nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            Set<Integer> set = new HashSet<>();
            for (int j = i; j < n; j++) {
                set.add(nums.get(j));
                int count = set.size();
                ans += count * count;
            }
        }
        return ans;
    }
}