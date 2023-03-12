using System.Linq;

namespace SO1.Algorithms;

public class SJFAlgorithm : IAlgorithm {
    private List<Process> processList;
    private List<Process> executedProcesses;

    public SJFAlgorithm(List<Process> processList) {
        this.processList = processList;
        executedProcesses = new();
    }

    public void Execute() {
        int tick = 1;

        while(processList.Any()) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted).OrderBy(p => p.Amount);
            if(!currentProcesses.Any()) {
                tick++;
                continue;
            }
            Process process = currentProcesses.First();
            process.Execute();

            tick += process.InitialAmount;
            currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted).OrderBy(p => p.Amount);
            foreach(var proc in currentProcesses) {
                proc.AddWaitingTime(tick - proc.ArrivalTime - proc.WaitingTime);
            }

            executedProcesses.Add(process);
            processList.Remove(process);
        }

        Console.WriteLine($"Średni czas oczekiwania dla SJF : {(float)executedProcesses.Sum(p => p.WaitingTime) / executedProcesses.Count}");
    }
}