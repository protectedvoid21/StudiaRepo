using System.Diagnostics;
using SO1.Algorithms;

namespace SO1;

public class Program {
    private static void Main() {
        //List<Process> processList = ProcessGenerator.GetProcessList(new[] { 4, 5, 1, 2 });
        List<Process> processList = ProcessGenerator.GetProcessList(5000, 50);

        IAlgorithm[] algorithms = {
            new FCFSAlgorithm(ProcessGenerator.CopyProcessList(processList)),
            new SJFAlgorithm(ProcessGenerator.CopyProcessList(processList)),
            new SRTFAlgorithm(ProcessGenerator.CopyProcessList(processList)),
            new RRAlgorithm(ProcessGenerator.CopyProcessList(processList), 15)
        };

        //ProcessGenerator.PrintProcessList(processList);

        foreach(var algorithm in algorithms) {
            algorithm.Execute();
        }
    }
}