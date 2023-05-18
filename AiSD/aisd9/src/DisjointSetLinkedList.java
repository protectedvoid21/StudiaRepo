public class DisjointSetLinkedList implements DisjointSetDataStructure {

	private class Element {
		int representant;
		int next;
		int length;
		int last;
	}

	private static final int NULL = -1;

	private Element[] arr;

	public DisjointSetLinkedList(int size) {
		arr = new Element[size];
	}

	@Override
	public void makeSet(int item) {
		arr[item] = new Element();
		arr[item].representant = item;
		arr[item].next = NULL;
		arr[item].length = 1;
		arr[item].last = item;
	}

	@Override
	public int findSet(int item) {
		return arr[item].representant;
	}

	@Override
	public boolean union(int itemA, int itemB) {
		int representantA = findSet(itemA);
		int representantB = findSet(itemB);

		if (representantA == representantB) {
			return false;
		}

		int biggerRepresentant = representantA;
		int smallerRepresentant = representantB;
		if(arr[representantA].length < arr[representantB].length) {
			biggerRepresentant = representantB;
			smallerRepresentant = representantA;
		}
		
		arr[arr[biggerRepresentant].last].next = smallerRepresentant;
		arr[biggerRepresentant].last = arr[smallerRepresentant].last;
		arr[biggerRepresentant].length += arr[smallerRepresentant].length;
		
		
		int current = smallerRepresentant;
		while (current != NULL) {
			arr[current].representant = biggerRepresentant;
			current = arr[current].next;
		}

		return true;
	}

	@Override
	public String toString() {
		String text = "Disjoint sets as linked list: \n";
		
		boolean[] printed = new boolean[arr.length];

		for (int i = 0; i < arr.length; i++) {
			if (!printed[arr[i].representant]) {
				int current = arr[i].representant;
				text += current;
				printed[arr[i].representant] = true;
				
				current = arr[current].next;
				while (current != NULL) {
					text += ", " + current;
					current = arr[current].next;
				}

				text += "\n";
			}
		}

		return text.trim();
	}
}