import java.util.*;
class Solution {
    public List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();
        if (digits == null || digits.length() == 0) {
            return result;
        }
        String[] keypad = {
            "", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };
        backtrack(digits, 0, new StringBuilder(), result, keypad);
        return result;
    }

    private void backtrack(String digits, int index,
                           StringBuilder current,
                           List<String> result,
                           String[] keypad) {
        if (index == digits.length()) {
            result.add(current.toString());
            return;
        }

        String letters = keypad[digits.charAt(index) - '0'];
        for (char ch : letters.toCharArray()) {
            current.append(ch);
            backtrack(digits, index + 1, current, result, keypad);
            current.deleteCharAt(current.length() - 1);
        }
    }
}
