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
                        link.add(createLink(word));
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
            }
            
            if(isSpecialCharacter(currentChar)) {
                return null;
            }
        }

        return readNumber ? null : new Link(refText) ;
    }
    
    private static boolean isSpecialCharacter(char c) {
        return !Character.isLetterOrDigit(c) && c != '_';
    }

    public static boolean correctLink(String link) {
        char firstChar = link.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return false;
        }

        for(int i = 1; i < link.length(); i++) {
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
        String str = "Document: " + name;
        for (var link : link) {
            str += "\n" + link.ref;
        }
        return str;
    }

    public String toStringReverse() {
        String retStr="Document: "+name;
        ListIterator<Link> iter=link.listIterator();
        while(iter.hasNext())
            iter.next();
        //TODO
        while(iter.hasPrevious()){
        }
        return retStr;
    }
}
