namespace SO1;

public class ProcessGenerator {
    public static List<Process> GetProcessList(int processCount, int maxAmount) {
        List<Process> processList = new();

        Random random = new();

        for(var i = 0; i < processCount; i++) {
            processList.Add(new Process(random.Next(1, maxAmount + 1), i/* + random.Next(1, 5)*/));
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