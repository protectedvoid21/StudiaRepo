using System.Diagnostics;
using SO1.Algorithms;

namespace SO1;

public class Program {
    private static void Main() {
        //List<Process> processList = ProcessGenerator.GetProcessList(new[] { 4, 5, 1, 2 });
        List<Process> processList = ProcessGenerator.GetProcessList(2500, 150);

        Algorithm[] algorithms = {
            new FCFSAlgorithm(ProcessGenerator.CopyProcessList(processList), "FCFS"),
            new SJFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SJF"),
            new SRTFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SRTF"),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 50)
        };

        //ProcessGenerator.PrintProcessList(processList);

        Console.WriteLine("Computing in progress...");
        List<AlgorithmStats> algorithmsStats = new();
        foreach(var algorithm in algorithms) {
            Console.WriteLine($"Executing {algorithm.Name}...");
            algorithm.Execute();
            Console.WriteLine($"Executed {algorithm.Name} successfully");
            algorithmsStats.Add(new AlgorithmStats(algorithm.ExecutedProcesses, algorithm.Name));
        }
        Console.Clear();

        AlgorithmAnalizer.Create(algorithmsStats);
    }
}