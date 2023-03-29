import java.util.Iterator;
import java.util.ListIterator;
import java.util.Scanner;

public class Document{
    public String name;
    public TwoWayCycledOrderedListWithSentinel<Link> link;
    
    public Document(String name, Scanner scan) {
        this.name=name.toLowerCase();
        link=new TwoWayCycledOrderedListWithSentinel<Link>();
        load(scan);
    }
    
    public void load(Scanner scan) {
        String input = scan.nextLine();

        while(!input.equals("eod")) {
            input = input.toLowerCase();
            String[] words = input.split(" ");

            for(var word : words) {
                if(word.startsWith("link=") && word.length() > 5) {
                    word = word.substring(5);

                    if(correctLink(word)) {
                        Link created = createLink(word);
                        if(created != null) {
                            link.add(created);
                        }
                    }
                }
            }

            input = scan.nextLine();
        }
    }

    public static Link createLink(String link) {
        char firstChar = link.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return null;
        }
        
        boolean readNumber = false;
        String refText = String.valueOf(firstChar);
        String weightText = "";

        for(int i = 1; i < link.length(); i++) {
            char currentChar = link.charAt(i);
            
            if(currentChar == ')' && readNumber) {
                if(i + 1 != link.length()) {
                    return null;
                }
                int weightNumber;
                
                try {
                    weightNumber = Integer.parseInt(weightText);
                }
                catch(NumberFormatException ex) {
                    return null;
                }
                
                return new Link(refText, weightNumber);
            }
            
            if(readNumber) {
                weightText += currentChar;
            }
            
            if(currentChar == '(' && readNumber == false) {
                readNumber = true;
                continue;
            }
            
            if(!readNumber) {
                refText += currentChar;
            }
            
            if(isSpecialCharacter(currentChar)) {
                return null;
            }
        }

        return readNumber ? null : new Link(link) ;
    }
    
    private static boolean isSpecialCharacter(char c) {
        return !Character.isLetterOrDigit(c) && c != '_';
    }

    public static boolean correctLink(String link) {
        char firstChar = link.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return false;
        }
        
        boolean hasLeftParenthesis = false;

        for(int i = 1; i < link.length(); i++) {
            if(link.charAt(i) == '(' && !hasLeftParenthesis) {
                hasLeftParenthesis = true;
                continue;
            }
            if(link.charAt(i) == ')') {
                if(hasLeftParenthesis) {
                    return i == link.length() - 1;
                }
                return false;
            }
            if(isSpecialCharacter(link.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    public static boolean isCorrectId(String id) {
        return correctLink(id);
    }

    @Override
    public String toString() {
        String str = "Document: " + name + "\n";

        int index = 1;
        for(var l : link) {
            str += l.toString() + " ";
            if(index == 10) {
                str = str.strip();
                str += "\n";
            }
            index++;
        }
        return str.strip();
    }

    public String toStringReverse() {
        String str = "Document: " + name + "\n";
        ListIterator<Link> iter = link.listIterator();
        
        while(iter.hasNext()) {
            iter.next();
        }
            
        int index = 1;
        while(iter.hasPrevious()){
            str += iter.previous().toString() + " ";
            if(index == 10) {
                str = str.strip();
                str += "\n";
            }
            index++;
        }
        
        return str.strip();
    }
}
