class Solution {
    public int minOperations(int[] nums, int x) {

        int totalSum = 0;

        for (int num : nums) {
            totalSum += num;
        }

        int target = totalSum - x;

        // If target is negative, impossible
        if (target < 0) {
            return -1;
        }

        // If target is 0, remove all elements
        if (target == 0) {
            return nums.length;
        }

        int left = 0;
        int currentSum = 0;
        int maxLength = -1;

        for (int right = 0; right < nums.length; right++) {

            currentSum += nums[right];

            // Reduce window if sum becomes greater than target
            while (left <= right && currentSum > target) {
                currentSum -= nums[left];
                left++;
            }

            // Found a valid subarray
            if (currentSum == target) {
                maxLength = Math.max(maxLength, right - left + 1);
            }
        }

        return maxLength == -1 ? -1 : nums.length - maxLength;
    }
}