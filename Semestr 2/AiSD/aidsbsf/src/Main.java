import java.util.List;

public class Main {
    public static void main(String[] args) {
        var nodes = new String[] {"a", "b", "c", "d", "e", "f", "g", "h", "i", "s", "t"};
        var edges = new Edge[] {
                new Edge("a", "d"), new Edge("a", "s"),
                new Edge("b", "s"), new Edge("b", "d"),
                new Edge("s", "c"), new Edge("c", "f"),
                new Edge("b", "e"), new Edge("e", "i"),
                new Edge("d", "g"), new Edge("g", "t"),
                new Edge("e", "g"), new Edge("e", "h"),
                new Edge("h", "i"), new Edge("h", "g"),
                new Edge("g", "i"), new Edge("h", "t"),
                new Edge("i", "t")
        };
        
        var graph = new Graph(nodes, edges);
        
        System.out.println("BFS - Przeszukiwanie wszerz : " + graph.bfs("s"));
        System.out.println();
        System.out.println("BFS - Przeszukiwanie wszerz : " + graph.bfs("e"));
        System.out.println("\n");
        
        System.out.println("DFS - Przeszukiwanie w głąb : " + graph.dfs("s"));
        System.out.println();
        System.out.println("DFS - Przeszukiwanie w głąb : " + graph.dfs("e"));
    }
}