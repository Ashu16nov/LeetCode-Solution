class Solution {
    public String reverseParentheses(String s) {
        StringBuilder sb = new StringBuilder(s);

        while (sb.indexOf("(") != -1) {
            int open = sb.lastIndexOf("(");
            int close = sb.indexOf(")", open);

            StringBuilder temp = new StringBuilder(
                sb.substring(open + 1, close)
            );

            temp.reverse();

            sb.replace(open, close + 1, temp.toString());
        }

        return sb.toString();
    }
}