import com.sun.source.tree.WhileLoopTree;

import java.util.*;
import java.util.Map.Entry;

public class Graph {
	private int arr[][];
	private HashMap<String, Integer> nodeIntMap;
	private HashMap<Integer, String> intNodeMap;

	public Graph(SortedMap<String, Document> internet) {
		int size = internet.size();
		arr = new int[size][size];
		nodeIntMap = new HashMap<>();
		intNodeMap = new HashMap<>();

		int documentIndex = 0;
		for(var document : internet.values()) {
			intNodeMap.put(documentIndex, document.name);
			nodeIntMap.put(document.name, documentIndex++);
		}

		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if(i == j) {
					arr[i][j] = 0;
					continue;
				}

				var link = internet.get(intNodeMap.get(i)).links.get(intNodeMap.get(j));
				if(link != null) {
					arr[i][j] = link.weight;
				}
				else {
					arr[i][j] = Integer.MAX_VALUE;
				}
			}
		}
	}

	public String bfs(String start) {
		if(!nodeIntMap.containsKey(start)) {
			return null;
		}

		var queue = new LinkedList<Integer>();
		var visited = new HashSet<Integer>();

		int index = nodeIntMap.get(start);
		visited.add(index);
		queue.add(index);

		String text = start;

		while(!queue.isEmpty()) {
			index = queue.pop();

			for(int i = 0; i < arr.length; i++) {
				if(index == i) {
					continue;
				}

				if(hasConnection(index, i) && !visited.contains(i)) {
					text += ", " + intNodeMap.get(i);
					visited.add(i);
					queue.add(i);
				}
			}
		}

		return text;
	}

	public String dfs(String start) {
		if(!nodeIntMap.containsKey(start)) {
			return null;
		}

		var visited = new LinkedList<Integer>();
		int startIndex = nodeIntMap.get(start);

		dfsBranch(startIndex, visited);

		String text = "";

		int visitedSize = visited.size();
		for(int i = 0; i < visitedSize; i++) {
			text += intNodeMap.get(visited.pop()) + ", ";
		}
		return text.substring(0, text.length() - 2);
	}

	private void dfsBranch(int start, LinkedList<Integer> visited) {
		if(visited.contains(start)) {
			return;
		}
		visited.add(start);
		for(int i = 0; i < arr.length; i++) {
			if(i == start) {
				continue;
			}

			if(hasConnection(start, i) && !visited.contains(i)) {
				dfsBranch(i, visited);
			}
		}
	}

	public int connectedComponents() {
		var forestSet = new DisjointSetForest(arr.length);

		for(int i = 0; i < arr.length; i++) {
			forestSet.makeSet(i);
		}

		for(int i = 0; i < arr.length; i++) {
			for(int j = 0; j < arr.length; j++) {
				if(arr[i][j] > 0) {
					forestSet.union(i, j);
				}
			}
		}
		return forestSet.countSets();
	}
	
	private boolean hasConnection(int beginNode, int endNode) {
		return arr[beginNode][endNode] > 0 && arr[beginNode][endNode] < Integer.MAX_VALUE;
	}
	
	private int getClosestNode(int[] roadCosts, boolean[] visited) {
		int minNode = -1;
		for(int i = 0; i < arr.length; i++) {
			if(!visited[i]) {
				if(minNode == -1) {
					minNode = i;
					continue;
				}
				if(roadCosts[i] < roadCosts[minNode]) {
					minNode = i;
				}
			}
		}
		return minNode;
	}
	
	public String DijkstraSSSP(String startVertexStr) {
		if(!nodeIntMap.containsKey(startVertexStr)) {
			return null;
		}
		var roadCosts = new int[arr.length];
		var nodeRoutes = new HashMap<Integer, ArrayList<Integer>>();
		var visited = new boolean[arr.length];
		
		for(int i = 0; i < arr.length; i++) {
			nodeRoutes.put(i, new ArrayList<>());
			roadCosts[i] = Integer.MAX_VALUE;
		}
		int current = nodeIntMap.get(startVertexStr);
		roadCosts[current] = 0;
		nodeRoutes.get(current).add(current);
		
		do {
			visited[current] = true;
			for(int i = 0; i < arr.length; i++) {
				if (!hasConnection(current, i) || visited[i] || roadCosts[current] == Integer.MAX_VALUE) {
					continue;
				}
				int newDistance = roadCosts[current] + arr[current][i];
				if(newDistance < roadCosts[i]) {
					var newRoute = (ArrayList<Integer>)nodeRoutes.get(current).clone();
					newRoute.add(i);
					nodeRoutes.put(i, newRoute);
					roadCosts[i] = newDistance;
				}
			}
			
			current = getClosestNode(roadCosts, visited);
		} while(current != -1);
		
		String text = "";
		for(int i = 0; i < arr.length; i++) {
			if(roadCosts[i] == Integer.MAX_VALUE) {
				text += "no path to " + intNodeMap.get(i) + "\n";
				continue;
			}
			var routeIterator = nodeRoutes.get(i).iterator();
			text += intNodeMap.get(routeIterator.next());
			
			while(routeIterator.hasNext()) {
				text += "->" + intNodeMap.get(routeIterator.next());
			}
			text += "=" + roadCosts[i] + "\n";
		}
		return text;
	}
}
