import org.w3c.dom.Text;

import java.util.*;

public class Graph {
    private int arr[][];
    private HashMap<String, Integer> name2Int;
    private HashMap<Integer, String> int2Name;
    
    public Graph(SortedMap<String, Document> internet) {
        int size = internet.size();
        arr = new int[size][size];
        name2Int = new HashMap<>();
        int2Name = new HashMap<>();
        
        int documentIndex = 0;
        for(var document : internet.values()) {
            int2Name.put(documentIndex, document.name);
            name2Int.put(document.name, documentIndex++);
        }
        
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(i == j) {
                    arr[i][j] = 0;
                    continue;
                }
                
                var link = internet.get(int2Name.get(i)).links.get(int2Name.get(j));
                if(link != null) {
                    arr[i][j] = link.weight;
                }
                else {
                    arr[i][j] = -1;
                }
            }
        }
    }

    public String bfs(String start) {
        if(!name2Int.containsKey(start)) {
            return null;
        }
        
        var queue = new LinkedList<Integer>();
        var visited = new HashSet<Integer>();
        
        int index = name2Int.get(start);
        visited.add(index);
        queue.add(index);
        
        String text = start;
        
        while(!queue.isEmpty()) {
            index = queue.pop();
            
            for(int i = 0; i < arr.length; i++) {
                if(index == i) {
                    continue;
                }
                
                if(arr[index][i] > 0 && !visited.contains(i)) {
                    text += ", " + int2Name.get(i);
                    visited.add(i);
                    queue.add(i);
                }
            }
        }
        
        return text;
    }

    public String dfs(String start) {
        if(!name2Int.containsKey(start)) {
            return null;
        }
        
        var visited = new LinkedList<Integer>();
        int startIndex = name2Int.get(start);
        
        dfsBranch(startIndex, visited);
        
        String text = "";
        
        int visitedSize = visited.size();
        for(int i = 0; i < visitedSize; i++) {
            text += int2Name.get(visited.pop()) + ", ";
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

            if(arr[start][i] > 0 && !visited.contains(i)) {
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
}
