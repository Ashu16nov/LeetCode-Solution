import java.util.*;

class Solution {
    public int[] maximumWeight(List<List<Integer>> intervals) {
        int n = intervals.size();

        // start, end, weight, original index
        int[][] arr = new int[n][4];

        for (int i = 0; i < n; i++) {
            arr[i][0] = intervals.get(i).get(0);
            arr[i][1] = intervals.get(i).get(1);
            arr[i][2] = intervals.get(i).get(2);
            arr[i][3] = i;
        }

        // Sort by ending time
        Arrays.sort(arr, (a, b) -> {
            if (a[1] != b[1]) {
                return Integer.compare(a[1], b[1]);
            }
            return Integer.compare(a[0], b[0]);
        });

        // Find previous non-overlapping interval
        int[] prev = new int[n];

        for (int i = 0; i < n; i++) {
            int lo = 0;
            int hi = i - 1;
            int ans = -1;

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;

                if (arr[mid][1] < arr[i][0]) {
                    ans = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            prev[i] = ans;
        }

        // dp[i][k] = maximum weight using first i intervals
        // and selecting at most k intervals
        long[][] dp = new long[n + 1][5];

        // Store selected original indices
        List<Integer>[][] path = new ArrayList[n + 1][5];

        for (int i = 0; i <= n; i++) {
            for (int k = 0; k <= 4; k++) {
                path[i][k] = new ArrayList<>();
            }
        }

        for (int i = 1; i <= n; i++) {

            for (int k = 0; k <= 4; k++) {

                // Skip current interval
                dp[i][k] = dp[i - 1][k];
                path[i][k] = new ArrayList<>(path[i - 1][k]);

                // Take current interval
                if (k > 0) {
                    int p = prev[i - 1] + 1;

                    long newWeight =
                            dp[p][k - 1] + arr[i - 1][2];

                    List<Integer> candidate =
                            new ArrayList<>(path[p][k - 1]);

                    candidate.add(arr[i - 1][3]);

                    Collections.sort(candidate);

                    if (newWeight > dp[i][k] ||
                        (newWeight == dp[i][k] &&
                         isSmaller(candidate, path[i][k]))) {

                        dp[i][k] = newWeight;
                        path[i][k] = candidate;
                    }
                }
            }
        }

        // Find best answer among 0 to 4 intervals
        List<Integer> best = new ArrayList<>();

        for (int k = 0; k <= 4; k++) {
            if (dp[n][k] > dp[n][best.size()] ||
                (dp[n][k] == dp[n][best.size()] &&
                 isSmaller(path[n][k], best))) {

                best = path[n][k];
            }
        }

        // Convert List<Integer> to int[]
        int[] answer = new int[best.size()];

        for (int i = 0; i < best.size(); i++) {
            answer[i] = best.get(i);
        }

        return answer;
    }

    private boolean isSmaller(List<Integer> a, List<Integer> b) {
        int len = Math.min(a.size(), b.size());

        for (int i = 0; i < len; i++) {
            if (!a.get(i).equals(b.get(i))) {
                return a.get(i) < b.get(i);
            }
        }

        return a.size() < b.size();
    }
}