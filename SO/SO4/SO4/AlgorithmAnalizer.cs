namespace SO4; 

public static class AlgorithmAnalizer {
    private const int tableWidth = 115;

    public static void Create(AlgorithmInitData data) {
        PrintRow(data.AlgorithmStats.Select(a => a.Name).Prepend("").ToArray());
        PrintLine();
        
        PrintRow(data.AlgorithmStats.Select(a => a.FailuresSum.ToString()).Prepend("Failures sum").ToArray());
        PrintLine();
        PrintRow(data.AlgorithmStats.Select(a => a.ProcessFailuresMean.ToString("F2")).Prepend("Failures mean").ToArray());
        PrintLine();
        PrintRow(data.AlgorithmStats.Select(a => a.ProcessFailuresMedian.ToString("F2")).Prepend("Failures median").ToArray());
        PrintLine();
        PrintRow(data.AlgorithmStats.Select(a => a.FailureStandardDeviation.ToString("F2")).Prepend("Failures std. dev.").ToArray());
        PrintLine();
        PrintLine();
        PrintRow("Page count", data.PageCount.ToString());
        PrintLine();
        PrintRow("Max request", data.MaxRequest.ToString());
        PrintLine();
        PrintRow("Process count", data.ProcessCount.ToString());
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