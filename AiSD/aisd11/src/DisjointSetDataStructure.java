public interface DisjointSetDataStructure{
	void makeSet(int item);
	int findSet(int item);
	boolean union(int itemA, int itemB);
	int countSets();
}
