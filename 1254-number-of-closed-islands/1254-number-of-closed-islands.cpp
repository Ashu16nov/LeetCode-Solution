class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        function<bool(int, int)> dfs = [&](int r, int c) -> bool {
            if (r < 0 || r >= m || c < 0 || c >= n)
                return false;
            if (grid[r][c] == 1)
                return true;

            grid[r][c] = 1;
            bool up = dfs(r - 1, c);
            bool down = dfs(r + 1, c);
            bool left = dfs(r, c - 1);
            bool right = dfs(r, c + 1);
            return up && down && left && right;
        };

        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && dfs(i, j)) {
                    count++;
                }
            }
        }
        return count;
    }
};
