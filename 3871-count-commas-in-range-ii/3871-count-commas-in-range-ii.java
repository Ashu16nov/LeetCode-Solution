class Solution {
    public long countCommas(long n) {
        long count = 0;
        long start = 1000;
        long commas = 1;

        while (start <= n) {
            long next = start * 1000;

            long end;
            if (next > n || next < start) {
                end = n;
            } else {
                end = next - 1;
            }

            count += (end - start + 1) * commas;

            start = next;
            commas++;
        }

        return count;
    }
}