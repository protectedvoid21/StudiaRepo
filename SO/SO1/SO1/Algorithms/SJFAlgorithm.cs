using System.Linq;

namespace SO1.Algorithms;

public class SJFAlgorithm : Algorithm {
    public SJFAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    public override void Execute() {
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

            ExecutedProcesses.Add(process);
            processList.Remove(process);
        }
    }
}