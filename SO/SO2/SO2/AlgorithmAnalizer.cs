namespace SO2;

public class AlgorithmAnalizer {
    private const int tableWidth = 50;

    public static void Create(List<AlgorithmStats> algorithmStats) {
        PrintRow(algorithmStats.Select(a => a.Name).Prepend("").ToArray());
        PrintLine();
        
        PrintRow(algorithmStats.Select(a => a.AverageWaiting.ToString("F3")).Prepend("Avg. waiting").ToArray());
        PrintLine();
        PrintRow(algorithmStats.Select(a => a.HeadMoves.ToString()).Prepend("Head moves").ToArray());
        PrintLine();
        PrintRow(algorithmStats.Select(a => a.MinWaiting.ToString()).Prepend("Min. waiting").ToArray());
        PrintLine();
        PrintRow(algorithmStats.Select(a => a.MaxWaiting.ToString()).Prepend("Max. waiting").ToArray());
        PrintLine();
        PrintRow(algorithmStats.Select(a => a.RequestCount.ToString()).Prepend("Request count").ToArray());
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