import java.util.ListIterator;
import java.util.Objects;
import java.util.Scanner;

public class Document implements IWithName{
	public String name;
	public TwoWayCycledOrderedListWithSentinel<Link> links;
	
	private final int[] key = { 7,11,13,17,19 };
	private static final int MODVALUE = 100000000;
	
	public Document(String name) {
		this.name = name.toLowerCase();
	}

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

	private static boolean isSpecialCharacter(char c) {
		return !Character.isLetterOrDigit(c) && c != '_';
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

	@Override
	public String getName() {
		return name;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Document document = (Document) o;
		return name.equals(document.getName());
	}

	@Override
	public int hashCode() {
		int keyIndex = 0;
		
		char[] chars = name.toCharArray();
		int code = chars[0];
		
		for(int i = 1; i < chars.length; i++) {
			code = (code * key[keyIndex] + chars[i]) % MODVALUE;
			keyIndex = ++keyIndex % key.length;
		}
		
		return code;
	}
}

