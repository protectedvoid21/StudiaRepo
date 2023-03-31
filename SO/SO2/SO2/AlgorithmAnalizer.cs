namespace SO2;

public class AlgorithmAnalizer {
    private const int tableWidth = 140;

    public static void Create() {
        throw new NotImplementedException();
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