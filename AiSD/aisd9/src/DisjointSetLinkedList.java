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
		if (arr[item].representant != item) {
			arr[item].representant = findSet(arr[item].representant);
		}
		return arr[item].representant;
	}

	@Override
	public boolean union(int itemA, int itemB) {
		int representantA = findSet(itemA);
		int representantB = findSet(itemB);

		if (representantA == representantB) {
			return false; // The items are already in the same set
		}

		// Append the tree represented by itemB to the tree represented by itemA
		arr[arr[representantA].last].next = representantB;
		arr[representantA].last = arr[representantB].last;
		arr[representantA].length += arr[representantB].length;

		// Update the representant of the appended tree
		int current = representantB;
		while (current != NULL) {
			arr[current].representant = representantA;
			current = arr[current].next;
		}

		return true;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < arr.length; i++) {
			sb.append("Item: ").append(i)
					.append(", Representant: ").append(arr[i].representant)
					.append(", Next: ").append(arr[i].next)
					.append(", Length: ").append(arr[i].length)
					.append(", Last: ").append(arr[i].last)
					.append("\n");
		}
		return sb.toString();
	}
}