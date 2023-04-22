namespace SO3; 

public class AlgorithmAnalizer {
    private const int tableWidth = 100;

    public static void Create(List<AlgorithmStats> algorithmStats, int requestCount, int maxRequest) {
        PrintRow(algorithmStats.Select(a => a.Name).Prepend("").ToArray());
        PrintLine();
        
        PrintRow(algorithmStats.Select(a => a.FailureCount.ToString()).Prepend("Failure count").ToArray());
        PrintLine();
        PrintRow("Request count", requestCount.ToString());
        PrintLine();
        PrintRow("Max request", maxRequest.ToString());
        PrintLine();
    }
    
    private static void PrintRow(params string[] columns) {
        int width = (tableWidth - columns.Length) / columns.Length;
        string row = "|";

        foreach(string column in columns) {
            row += AlignCentre(column, width) + "|";
        }

        Console.WriteLine(row);
    }

    private static string AlignCentre(string text, int width) {
        text = text.Length > width ? text.Substring(0, width - 3) + "..." : text;

        if(string.IsNullOrEmpty(text)) {
            return new string(' ', width);
        }
        return text.PadRight(width - (width - text.Length) / 2).PadLeft(width);
    }

    private static void PrintLine() {
        Console.WriteLine(new string('-', tableWidth + 1));
    }
}