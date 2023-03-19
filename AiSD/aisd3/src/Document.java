import java.util.Scanner;

public class Document {
    public String name;
    public TwoWayUnorderedListWithHeadAndTail<Link> links;

    public Document(String name, Scanner scan) {
        this.name = name;
        links = new TwoWayUnorderedListWithHeadAndTail<Link>();
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
                        links.add(new Link(word));
                    }
                }
            }

            input = scan.nextLine();
        }
    }

    public static boolean correctLink(String link) {
        char firstChar = link.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return false;
        }

        return containsSpecialCharacters(link);
    }

    private static boolean containsSpecialCharacters(String text) {
        char[] chars = text.toCharArray();

        for (var c : chars) {
            if (!Character.isLetterOrDigit(c) && c != '_') {
                return false;
            }
        }
        return true;
    }

    @Override
    public String toString() {
        String str = "Document: " + name + "\n";
        for (var link : links) {
            str += link.ref + "\n";
        }
        str = str.strip();
        return str;
    }

    public String toStringReverse() {
        String retStr = "Document: " + name + "\n";
        return retStr + links.toStringReverse();
    }

}