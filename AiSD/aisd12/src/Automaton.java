import java.util.LinkedList;

public class Automaton implements IStringMatcher {

    @Override
    public LinkedList<Integer> validShifts(String pattern, String text) {
        LinkedList<Integer> shifts = new LinkedList<>();

        int m = pattern.length();
        int n = text.length();

        int lowerCode = 256;
        int biggerCode = 0;
        
        for (int i = 0; i < n; i++) {
            int code = text.charAt(i);
            if (code < lowerCode) {
                lowerCode = code;
            }
            if (code > biggerCode) {
                biggerCode = code;
            }
        }
        
        int alphabetSize = biggerCode - lowerCode + 1;
        int[][] automaton = buildAutomaton(pattern, alphabetSize, lowerCode);

        int state = 0;

        for (int i = 0; i < n; i++) {
            int code = text.charAt(i) - lowerCode;
            state = automaton[state][code];

            if (state == m) {
                int shift = i - m + 1;
                shifts.add(shift);
            }
        }

        return shifts;
    }

    private int[][] buildAutomaton(String pattern, int alphabetSize, int lowerCode) {
        int patternLen = pattern.length();

        int[][] automaton = new int[patternLen + 1][alphabetSize];

        for (int state = 0; state <= patternLen; state++) {
            for (int i = 0; i < alphabetSize; i++) {
                char character = (char) (i + lowerCode);
                
                if (state < patternLen && pattern.charAt(state) == character) {
                    automaton[state][i] = state + 1;
                }
                else {
                    automaton[state][i] = nextState(pattern, state, character);
                }
            }
        }

        return automaton;
    }

    private int nextState(String pattern, int state, char character) {
		int nextState = 0;

        for (int i = state; i > 0; i--) {
            if (pattern.charAt(i - 1) == character) {
                int j = 0;
                while (j < i - 1 && pattern.charAt(j) == pattern.charAt(state - i + 1 + j)) {
                    j++;
                }
                if (j == i - 1) {
                    nextState = i;
                    break;
                }
            }
        }

        return nextState;
    }
}
