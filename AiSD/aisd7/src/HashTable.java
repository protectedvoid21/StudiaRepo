import java.util.LinkedList;

public class HashTable{
	LinkedList[] arr; // use pure array
	private final static int defaultInitSize=8;
	private final static double defaultMaxLoadFactor=0.7;
	private int size;	
	private int currentSize;
	private final double maxLoadFactor;
	
	public HashTable() {
		this(defaultInitSize);
	}
	public HashTable(int size) {
		this(size,defaultMaxLoadFactor);
	}
	
	public HashTable(int initCapacity, double maxLF) {
		this.size = initCapacity;
		this.maxLoadFactor=maxLF;
		
		arr = new LinkedList[size];
		for(int i = 0; i < size; i++) {
			arr[i] = new LinkedList();
		}
	}

	public boolean add(Object elem) {
		if(contains(elem)) {
			return false;
		}
		
		if(currentSize + 1 > maxLoadFactor * size) {
			doubleArray();
		}
		
		int hash = elem.hashCode() % size;
		arr[hash].add(elem);
		currentSize++;
		
		return true;
	}
	
	private boolean contains(Object elem) {
		var searchedList = arr[elem.hashCode() % size];

		for(var e : searchedList) {
			if(e.equals(elem)) {
				return true;
			}
		}
		return false;
	}

	private void doubleArray() {
		size *= 2;
		LinkedList[] newArr = new LinkedList[size];
		
		for (int i = 0; i < size; i++) {
			newArr[i] = new LinkedList();
		}

		for (var list : arr) {
			for (var elem : list) {
				int hash = elem.hashCode() % size;
				newArr[hash].add(elem);
			}
		}
		arr = newArr;
	}


	@Override
	public String toString() {
		String text = "";
		
		for(int i = 0; i < arr.length; i++) {
			text += i + ":";
			for(var elem : arr[i]) {
				IWithName elemWithName = (IWithName)elem; 
				text += " " + elemWithName.getName() + ",";
			}
			if(text.charAt(text.length() - 1) != ':') {
				text = text.substring(0, text.length() - 1);
			}
			text += "\n";
		}
		return text;
	}

	public Object get(Object toFind) {
		var searchedList = arr[toFind.hashCode() % size];

		for(var elem : searchedList) {
			if(elem.equals(toFind)) {
				return elem;
			}
		}
		
		return null;
	}
	
}

