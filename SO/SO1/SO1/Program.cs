using SO1.Algorithms;

namespace SO1;

public class Program {
    private static void Main() {
        List<Process> processList = ProcessGenerator.GetProcessList(100, 100, 200000).OrderBy(p => p.ArrivalTime).ToList();

        Algorithm[] algorithms = {
            new FCFSAlgorithm(ProcessGenerator.CopyProcessList(processList), "FCFS"),
            new SJFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SJF"),
            new SRTFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SRTF"),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 40),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 70),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 100)
        };

        Console.WriteLine("Computing in progress... (this may take a while)");
        List<AlgorithmStats> algorithmsStats = new();
        foreach(var algorithm in algorithms) {
            Console.WriteLine($"Executing {algorithm.Name}...");
            algorithm.Execute();
            Console.WriteLine($"Executed {algorithm.Name} successfully");
            algorithmsStats.Add(new AlgorithmStats(algorithm));
        }
        Console.Clear();

        AlgorithmAnalizer.Create(algorithmsStats);
    }
}