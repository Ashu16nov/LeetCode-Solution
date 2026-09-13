class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        vector<pair<int, int>> ones1, ones2;

        int n = img1.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1)
                    ones1.push_back({i, j});
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img2[i][j] == 1)
                    ones2.push_back({i, j});
            }
        }

        map<pair<int, int>, int> count;
        int ans = 0;

        for (auto p1 : ones1) {
            for (auto p2 : ones2) {
                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;

                count[{dx, dy}]++;

                ans = max(ans, count[{dx, dy}]);
            }
        }

        return ans;
    }
};