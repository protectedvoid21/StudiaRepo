import java.util.*;

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
                    arr[i][j] = -1;
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
                
                if(arr[index][i] > 0 && !visited.contains(i)) {
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
