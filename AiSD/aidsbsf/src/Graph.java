import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;

public class Graph {
    private HashMap<String, Integer> nodeIntMap;
    private String[] nodes;
    
    private int[][] numEdges;
    
    public Graph(String[] nodes, Edge[] edges) {
        nodeIntMap = new HashMap<>();
        this.nodes = nodes;
        numEdges = new int[nodes.length][nodes.length];
        
        for(int i = 0; i < nodes.length; i++) {
            nodeIntMap.put(nodes[i], i);
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
                    text += ", " + nodes[i];
                    visited.add(i);
                    queue.add(i);
                }
            }
        }

        return text;
    }

    public String dfs(String start) {
        var visited = new boolean[nodes.length];
        int startIndex = nodeIntMap.get(start);
        
        String text = dfsBranch(startIndex, visited);
        return text.substring(0, text.length() - 2);
    }

    private String dfsBranch(int start, boolean[] visited) {
        if(visited[start]) {
            return "";
        }
        visited[start] = true;

        String text = nodes[start] + ", ";
        for(int i = 0; i < numEdges.length; i++) {
            if(i == start) {
                continue;
            }

            if(numEdges[start][i] > 0 && !visited[i]) {
                text += dfsBranch(i, visited);
            }
        }
        return text;
    }
}
