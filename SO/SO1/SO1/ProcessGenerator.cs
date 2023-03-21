namespace SO1;

public class ProcessGenerator {
    public static List<Process> GetProcessList(int processCount, int maxAmount, int arrivalOffset) {
        List<Process> processList = new();

        Random random = new();

        for(var i = 0; i < processCount; i++) {
            processList.Add(new Process(random.Next(1, maxAmount + 1), i + random.Next(arrivalOffset)));
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
            new Process(1, 1),
            new Process(2, 1),
            new Process(3, 1),
            new Process(4, 1),
            new Process(5, 1),
            new Process(6, 1),
            new Process(1, 17),
            new Process(2, 17),
            new Process(3, 17),
            new Process(4, 17),
            new Process(1, 28),
            new Process(2, 28),
            new Process(3, 28),
        };
    }

    public static List<Process> TestRR() {
        return new List<Process> {
            new Process(1, 1),
            new Process(2, 1),
            new Process(4, 1),
            new Process(6, 1),
            new Process(8, 1),
            new Process(8, 12),
            new Process(6, 12),
            new Process(4, 12),
            new Process(2, 12),
            new Process(1, 12),
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