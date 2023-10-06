import java.util.LinkedList;
import java.util.HashSet;
import java.util.jar.JarEntry;

public class Automaton implements IStringMatcher {
    @Override
    public LinkedList<Integer> validShifts(String pattern, String text) {
        int lowerCode = 256;
        int biggerCode = 0;
        
        for(int i = 0; i < text.length(); i++) {
            int code = text.charAt(i);
            if (code < lowerCode) {
                lowerCode = code;
            }
            if (code > biggerCode) {
                biggerCode = code;
            }
        }
        
        for (int i = 0; i < pattern.length(); i++) {
            int code = pattern.charAt(i);
            if (code < lowerCode) {
                lowerCode = code;
            }
            if (code > biggerCode) {
                biggerCode = code;
            }
        }
        
        var automaton = computeTransition(pattern, lowerCode, biggerCode);
        var valid = new LinkedList<Integer>();
        int q = 0;
        for(int i = 0; i < text.length(); i++) {
            q = automaton[q][text.charAt(i) - lowerCode];
            
            if(q == pattern.length()) {
                valid.add(i - pattern.length() + 1);
            }
        }
        
        return valid;
    }
    
    private int[][] computeTransition(String pattern, int lowerCode, int biggerCode) {
        var automaton = new int[pattern.length() + 1][biggerCode - lowerCode + 1]; 
        
        int m = pattern.length();
        for(int q = 0; q <= m; q++) {
            for(int a = 0; a < automaton[0].length; a++) {
                int k = Math.min(m + 1, q + 2);
                do {
                    k--;
                } while(!(pattern.substring(0, q) + (char)(a + lowerCode)).endsWith(pattern.substring(0, k)));
                automaton[q][a] = k;
            }
        }
        
        return automaton;
    }
}
