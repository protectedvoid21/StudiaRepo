import java.util.HashSet;
import java.util.LinkedList;

public class KMP implements IStringMatcher {
    @Override
    public LinkedList<Integer> validShifts(String pattern, String text) {
        var prefixArr = buildPrefixArray(pattern);
		
		var valid = new LinkedList<Integer>();
		int q = 0;
		for(int i = 0; i < text.length(); i++) {
			while (q > 0 && pattern.charAt(q) != text.charAt(i)) {
				q = prefixArr[q - 1];
			}
			if(pattern.charAt(q) == text.charAt(i)) {
				q++;
			}
			if(q == pattern.length()) {
				valid.add(i - pattern.length() + 1);
				q = prefixArr[q - 1];
			}
		}
		
		return valid;
    }
	
	private int[] buildPrefixArray(String pattern) {
		var prefixArr = new int[pattern.length()];
		
		int m = pattern.length();
		int k = 0;
		for (int i = 1; i < m; i++) {
			while(k > 0 && pattern.charAt(k) != pattern.charAt(i)) {
				k = prefixArr[k - 1];
			}
			if(pattern.charAt(k) == pattern.charAt(i)) {
				k++;
			}
			prefixArr[i] = k;
		}
		
		return prefixArr;
	}
}
