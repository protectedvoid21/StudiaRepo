using System.Diagnostics;
using SO1.Algorithms;

namespace SO1;

public class Program {
    private static void Main() {
        //List<Process> processList = ProcessGenerator.GetProcessList(new[] { 4,5,1,2 });
        List<Process> processList = ProcessGenerator.GetProcessList(5000, 150, 200).OrderBy(p => p.ArrivalTime).ToList();
        //List<Process> processList = ProcessGenerator.GenerateSampleProcessList();

        Algorithm[] algorithms = {
            new FCFSAlgorithm(ProcessGenerator.CopyProcessList(processList), "FCFS"),
            new SJFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SJF"),
            new SRTFAlgorithm(ProcessGenerator.CopyProcessList(processList), "SRTF"),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 25),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 70),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), "RR", 150)
        };

        //ProcessGenerator.PrintProcessList(processList);

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