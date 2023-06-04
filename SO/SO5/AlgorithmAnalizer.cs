namespace SO5; 

public static class AlgorithmAnalizer {
    private const int tableWidth = 115;

    public static void Create(List<AlgorithmStats> data) {
        PrintRow(data.Select(a => a.Name).Prepend("").ToArray());
        PrintLine();
        
        PrintRow(data.Select(a => a.AverageProcessorLoad.ToString("F2")).Prepend("Avg. processor load").ToArray());
        PrintLine();
        PrintRow(data.Select(a => a.AverageLoadDeviation.ToString("F2")).Prepend("Avg. load deviation").ToArray());
        PrintLine();
        PrintRow(data.Select(a => a.AskedCount.ToString()).Prepend("Asked count").ToArray());
        PrintLine();
        PrintRow(data.Select(a => a.MigrationCount.ToString()).Prepend("Migration count").ToArray());
        PrintLine();
        PrintLine();
        /*PrintRow("Page count", data.PageCount.ToString());
        PrintLine();
        PrintRow("Max request", data.MaxRequest.ToString());
        PrintLine();
        PrintRow("Process count", data.ProcessCount.ToString());
        PrintLine();*/
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