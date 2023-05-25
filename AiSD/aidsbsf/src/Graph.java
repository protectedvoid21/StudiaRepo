import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;

public class Graph {
    private HashMap<String, Integer> nodeIntMap;
    private HashMap<Integer, String> intNodeMap;
    
    private int[][] numEdges;
    
    public Graph(String[] nodes, Edge[] edges) {
        nodeIntMap = new HashMap<>();
        intNodeMap = new HashMap<>();
        numEdges = new int[nodes.length][nodes.length];
        
        for(int i = 0; i < nodes.length; i++) {
            nodeIntMap.put(nodes[i], i);
            intNodeMap.put(i, nodes[i]);
        }
        
        for(int i = 0; i < nodes.length; i++) {
            for(int j = 0; j < nodes.length; j++) {
                if(i == j) {
                    numEdges[i][j] = 0;
                    continue;
                }
                numEdges[i][j] = -1;
            }
        }
        
        for(var edge : edges) {
            numEdges[nodeIntMap.get(edge.begin())][nodeIntMap.get(edge.end())] = 1;
            numEdges[nodeIntMap.get(edge.end())][nodeIntMap.get(edge.begin())] = 1;
        }
    }
    
    public String bfs(String start) {
        var queue = new LinkedList<Integer>();
        var visited = new HashSet<Integer>();

        int index = nodeIntMap.get(start);
        visited.add(index);
        queue.add(index);

        String text = start;

        while(!queue.isEmpty()) {
            index = queue.pop();

            for(int i = 0; i < numEdges.length; i++) {
                if(index == i) {
                    continue;
                }

                if(numEdges[index][i] > 0 && !visited.contains(i)) {
                    text += ", " + intNodeMap.get(i);
                    visited.add(i);
                    queue.add(i);
                }
            }
        }

        return text;
    }

    public String dfs(String start) {
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
        for(int i = 0; i < numEdges.length; i++) {
            if(i == start) {
                continue;
            }

            if(numEdges[start][i] > 0 && !visited.contains(i)) {
                dfsBranch(i, visited);
            }
        }
    }
}
