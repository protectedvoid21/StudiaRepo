import java.util.HashSet;

public class DisjointSetForest implements DisjointSetDataStructure {

	class Element {
		int rank;
		int parent;
	}

	Element[] arr;

	public DisjointSetForest(int size) {
		arr = new Element[size];
	}

	@Override
	public void makeSet(int item) {
		arr[item] = new Element();
		arr[item].parent = item;
		arr[item].rank = 0;
	}

	@Override
	public int findSet(int item) {
		if (arr[item].parent != item) {
			arr[item].parent = findSet(arr[item].parent);
		}
		return arr[item].parent;
	}

	@Override
	public boolean union(int itemA, int itemB) {
		int rootA = findSet(itemA);
		int rootB = findSet(itemB);

		if (rootA == rootB) {
			return false;
		}

		if (arr[rootA].rank < arr[rootB].rank) {
			arr[rootA].parent = rootB;
		}
		else if (arr[rootA].rank > arr[rootB].rank) {
			arr[rootB].parent = rootA;
		}
		else {
			arr[rootA].parent = rootB;
			arr[rootB].rank++;
		}

		return true;
	}

	@Override
	public String toString() {
		String text = "Disjoint sets as forest:\n";

		for (int i = 0; i < arr.length; i++) {
			text += i + " -> " + arr[i].parent + "\n";
		}
		return text.trim();
	}

	@Override
	public int countSets() {
		var sets = new HashSet<Integer>();

		for(int i = 0; i < arr.length; i++) {
			sets.add(findSet(i));
		}
		return sets.size();
	}
}
