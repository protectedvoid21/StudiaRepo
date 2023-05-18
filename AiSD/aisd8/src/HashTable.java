package dsaa.lab08;

import java.util.LinkedList;

public class HashTable{
	LinkedList arr[]; 
	private final static int defaultInitSize=8;
	private final static double defaultMaxLoadFactor=0.7;
	private int size;	
	private final double maxLoadFactor;
	public HashTable() {
		this(defaultInitSize);
	}
	public HashTable(int size) {
		this(size,defaultMaxLoadFactor);
	}


	public HashTable(int initCapacity, double maxLF) {
		
		if(initCapacity<2)
			initCapacity=2;
		arr=new LinkedList[initCapacity];
		//TODO
		maxLoadFactor=0.0;
	}

	public boolean add(Object elem) {
		//TODO
		return true;
	}

	@Override
	public String toString() {
		//TODO
		return null;
	}

	public Object get(Object toFind) {
		//TODO
		return null;
	}
	
}

