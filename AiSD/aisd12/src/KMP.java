import java.util.HashSet;
import java.util.LinkedList;

public class KMP implements IStringMatcher {
    @Override
    public LinkedList<Integer> validShifts(String pattern, String text) {
        var prefixArr = new int[pattern.length()];

		var existingChars = new HashSet<Character>();
		existingChars.add(pattern.charAt(0));
		int val = 0;
        for (int i = 1; i < pattern.length(); i++) {
            if(!existingChars.add(pattern.charAt(i))) {
				val++;
			}
			else {
				val = 0;
			}
			prefixArr[i] = val;
        }
		
		var valid = new LinkedList<Integer>();
		for(int i = 0; i <= text.length() - pattern.length(); i++) {
			for(int j = 0; j < pattern.length(); j++) {
				if(text.charAt(i + j) != pattern.charAt(j)) {
					i += prefixArr[j];
					break;
				}
				if(j == pattern.length() - 1) {
					valid.add(i);
				}
			}
		}
		
		return valid;
    }
}
