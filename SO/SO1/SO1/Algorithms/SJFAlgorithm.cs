using System.Linq;

namespace SO1.Algorithms;

public class SJFAlgorithm : Algorithm {
    private int tick;
    
    public SJFAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    private Process GetCurrentProcess() {
        Process process = processList[0];
        foreach (var proc in processList) {
            if (proc.ArrivalTime <= tick && proc.Amount < process.Amount) {
                process = proc;
            }
        }

        return process;
    }

    public override void Execute() {
        tick = 1;

        while(processList.Count > 0) {
            if(Utils.IsAnyProcessWaiting(processList, tick) == false) {
                tick++;
                continue;
            }

            Process currentProcess = GetCurrentProcess();
            currentProcess.Execute();
            ChangeCount++;
            
            ExecutedProcesses.Add(currentProcess);
            processList.Remove(currentProcess);

            tick += currentProcess.InitialAmount;
            
            var restProcesses = processList.Where(p => p.ArrivalTime <= tick);
            foreach(var proc in restProcesses) {
                proc.AddWaitingTime(tick - proc.ArrivalTime - proc.WaitingTime);
            }
        }
    }
}