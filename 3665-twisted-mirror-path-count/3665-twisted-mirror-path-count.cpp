
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<int> dp(n, 0);
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            int left = 0;

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    // Mirror: swap directions
                    int temp = left;
                    left = dp[j];
                    dp[j] = temp;
                }
                else {
                    // Empty cell: combine both paths
                    left = (left + dp[j]) % MOD;
                    dp[j] = left;
                }
            }
        }

        return dp[n - 1];
    }
};
