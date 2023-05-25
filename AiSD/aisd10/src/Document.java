import java.util.Scanner;
import java.util.*;

public class Document implements IWithName {
    public String name;
    // TODO? You can change implementation of Link collection
    public SortedMap<String, Link> links;

    public Document(String name) {
        this.name = name.toLowerCase();
        links = new TreeMap<String, Link>();
    }

    public Document(String name, Scanner scan) {
        this.name = name.toLowerCase();
        links = new TreeMap<String, Link>();
        load(scan);
    }

    public void load(Scanner scan) {
        String input = scan.nextLine();

        while (!input.equals("eod")) {
            input = input.toLowerCase();
            String[] words = input.split(" ");

            for (var word : words) {
                if (word.startsWith("link=") && word.length() > 5) {
                    word = word.substring(5);

                    if (correctLink(word)) {
                        Link created = createLink(word);
                        if (created != null) {
                            links.put(created.ref, created);
                        }
                    }
                }
            }

            input = scan.nextLine();
        }
    }

    public static boolean correctLink(String link) {
        return createLink(link) != null;
    }

    public static boolean isCorrectId(String id) {
        char firstChar = id.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return false;
        }

        for (int i = 1; i < id.length(); i++) {
            if (!Character.isLetterOrDigit(id.charAt(i)) && id.charAt(i) != '_') {
                return false;
            }
        }
        return true;
    }
    
    public static Link createLink(String link) {
        char firstChar = link.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return null;
        }

        boolean readNumber = false;
        String refText = String.valueOf(firstChar);
        String weightText = "";

        for (int i = 1; i < link.length(); i++) {
            char currentChar = link.charAt(i);

            if (currentChar == ')' && readNumber) {
                if (i + 1 != link.length()) {
                    return null;
                }
                int weightNumber;

                try {
                    weightNumber = Integer.parseInt(weightText);
                } catch (NumberFormatException ex) {
                    return null;
                }

                return new Link(refText, weightNumber);
            }

            if (readNumber) {
                weightText += currentChar;
            }

            if (currentChar == '(' && readNumber == false) {
                readNumber = true;
                continue;
            }

            if (!readNumber) {
                refText += currentChar;
            }

            if (isSpecialCharacter(currentChar)) {
                return null;
            }
        }

        return readNumber ? null : new Link(link);
    }

    private static boolean isSpecialCharacter(char c) {
        return !Character.isLetterOrDigit(c) && c != '_';
    }

    @Override
    public String toString() {
        String retStr = "Document: " + name + "\n";
        for(var entry : links.entrySet()) {
            retStr += entry.getValue().toString() + "\n";
        }
        return retStr;
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }

    @Override
    public String getName() {
        return name;
    }
}
