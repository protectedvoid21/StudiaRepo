import java.util.Scanner;

public class Document{
    public String name;
    public TwoWayUnorderedListWithHeadAndTail<Link> link;
    public Document(String name, Scanner scan) {
        this.name=name;
        link=new TwoWayUnorderedListWithHeadAndTail<Link>();
        load(scan);
    }
    public void load(Scanner scan) {
        //TODO
    }
    // accepted only small letters, capitalic letter, digits nad '_' (but not on the begin)
    public static boolean correctLink(String link) {
        //TODO
        return true;
    }

    @Override
    public String toString() {
        // TODO
        return null;
    }

    public String toStringReverse() {
        String retStr="Document: "+name;
        return retStr+link.toStringReverse();
    }

}