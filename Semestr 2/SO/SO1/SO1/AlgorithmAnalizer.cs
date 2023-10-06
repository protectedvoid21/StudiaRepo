using SO1.Algorithms;

namespace SO1; 

public class AlgorithmAnalizer {
    private const int tableWidth = 140;

    public static void Create(List<AlgorithmStats> algorithmStatList) {
        PrintRow(algorithmStatList.Select(a => a.Name).Prepend("").ToArray());
        PrintLine();

        PrintRow(algorithmStatList.Select(a => a.AverageExecution.ToString("F3")).Prepend("Avg. waiting").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.ProcessCount.ToString()).Prepend("Process count").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.ChangeCount.ToString()).Prepend("Change count").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.AverageProcessSize.ToString("F2")).Prepend("Avg. process size").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.MinWaiting.ToString()).Prepend("Min. waiting time").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.MaxWaiting.ToString()).Prepend("Max. waiting time").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.SmallestProcess.ToString()).Prepend("Smallest process").ToArray());
        PrintLine();
        PrintRow(algorithmStatList.Select(a => a.BiggestProcess.ToString()).Prepend("Biggest process").ToArray());
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