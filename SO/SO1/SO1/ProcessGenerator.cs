namespace SO1;

public class ProcessGenerator {
    public static List<Process> GetProcessList(int processCount, int maxAmount, int arrivalRange) {
        List<Process> processList = new();

        Random random = new();

        for(var i = 0; i < processCount; i++) {
            processList.Add(new Process(random.Next(1, maxAmount + 1), random.Next(arrivalRange)));
        }

        return processList;
    }

    public static List<Process> GetProcessList(IEnumerable<int> processLenghts) {
        List<Process> processList = new();

        int arrival = 1;
        foreach(var process in processLenghts) {
            processList.Add(new Process(process, arrival));
            arrival++;
        }

        return processList;
    }

    public static List<Process> GenerateSampleProcessList() {
        return new List<Process> {
            new(1, 1),
            new(2, 1),
            new(3, 1),
            new(4, 1),
            new(5, 1),
            new(6, 1),
            new(1, 17),
            new(2, 17),
            new(3, 17),
            new(4, 17),
            new(1, 28),
            new(2, 28),
            new(3, 28),
        };
    }

    public static List<Process> TestRR() {
        return new List<Process> {
            new(1, 1),
            new(2, 1),
            new(4, 1),
            new(6, 1),
            new(8, 1),
            new(8, 12),
            new(6, 12),
            new(4, 12),
            new(2, 12),
            new(1, 12),
        };
    }

    public static void PrintProcessList(List<Process> processes) {
        string text = "[";
        foreach(Process process in processes) {
            text += $" {process.Amount},";
        }

        text = text.Remove(text.Length - 1);
        text += " ]";
        Console.WriteLine(text);
    }

    public static List<Process> CopyProcessList(List<Process> processList) {
        return processList.Select(process => new Process(process.Amount, process.ArrivalTime)).ToList();
    }
}