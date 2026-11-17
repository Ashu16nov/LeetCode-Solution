class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size(), INF = 1e9;
        vector<vector<int>> c(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int d = 1; d < j - i + 1; d++)
                    if ((j - i + 1) % d == 0) {
                        int x = 0;
                        for (int r = 0; r < d; r++)
                            for (int a = i + r, b = j - d + 1 + r;
                                 a < b; a += d, b -= d)
                                x += s[a] != s[b];
                        c[i][j] = min(c[i][j], x);
                    }

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;

        for (int i = 2; i <= n; i++)
            for (int p = 1; p <= k; p++)
                for (int j = 0; j <= i - 2; j++)
                    dp[i][p] = min(dp[i][p], dp[j][p-1] + c[j][i-1]);

        return dp[n][k];
    }
};
