import java.io.Console;
import java.util.ListIterator;
import java.util.Scanner;

public class Document{
    public String name;
    public TwoWayCycledOrderedListWithSentinel<Link> links;
    public Document(String name, Scanner scan) {
        this.name=name.toLowerCase();
        links =new TwoWayCycledOrderedListWithSentinel<Link>();
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
                            links.add(created);
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

        return readNumber ? null : new Link(link);
    }

    private static boolean isSpecialCharacter(char c) {
        return !Character.isLetterOrDigit(c) && c != '_';
    }

    public static boolean correctLink(String link) {
        return createLink(link) != null;
    }

    public static boolean isCorrectId(String id) {
        char firstChar = id.charAt(0);

        if (!Character.isLetter(firstChar)) {
            return false;
        }

        for(int i = 1; i < id.length(); i++) {
            if(!Character.isLetterOrDigit(id.charAt(i)) && id.charAt(i) != '_') {
                return false;
            }
        }
        return true;
    }

    @Override
    public String toString() {
        String str = "Document: " + name + "\n";

        int index = 1;
        for(var l : links) {
            str += l.toString() + " ";
            if(index % 10 == 0) {
                str = str.strip();
                str += "\n";
            }
            index++;
        }
        return str.strip();
    }

    public String toStringReverse() {
        String str = "Document: " + name + "\n";
        ListIterator<Link> iter = links.listIterator();

        while(iter.hasNext()) {
            iter.next();
        }

        int index = 1;
        while(iter.hasPrevious()){
            str += iter.previous().toString() + " ";
            if(index % 10 == 0) {
                str = str.strip();
                str += "\n";
            }
            index++;
        }

        return str.strip();
    }
    
    public int[] getWeights() {
        int[] weights = new int[links.size()];
        var iter = links.iterator();
        
        for(int i = 0; iter.hasNext(); i++) {
            weights[i] = iter.next().weight;
        }
        return weights;
    }

    public static void showArray(int[] arr) {
        String arrayText = "";
        for(var num : arr) {
            arrayText += num + " ";
        }
        
        System.out.println(arrayText.strip());
    }
    
    private void swap(int[] arr, int left, int right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }

    void bubbleSort(int[] arr) {
        showArray(arr);
        
        for(int i = 0; i < arr.length - 1; i++) {
            for(int j = arr.length - 1; j > i; j--) {
                if(arr[j - 1] > arr[j]) {
                    swap(arr, j - 1, j);
                }
            }
            showArray(arr);
        }
    }

    public void insertSort(int[] arr) {
        showArray(arr);
        
        int sortedStart = arr.length - 1;
        for(int i = 0; i < arr.length - 1; i++) {
            for(int j = sortedStart; j < arr.length; j++) {
                if(arr[j - 1] > arr[j]) {
                    swap(arr, j - 1, j);
                }
                else {
                    break;
                }
            }
            sortedStart--;
            showArray(arr);
        }
    }
    
    public void selectSort(int[] arr) {
        showArray(arr);
        for(int i = 0; i < arr.length - 1; i++) {
            int maxIndex = 0;
            for(int j = 1; j < arr.length - i; j++) {
                if(arr[maxIndex] < arr[j]) {
                    maxIndex = j;
                }
            }
            swap(arr, maxIndex, arr.length - i - 1);
            showArray(arr);
        }
    }
}