namespace SO1.Algorithms;

public class SRTFAlgorithm : Algorithm {
    private int tick;
    
    public SRTFAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    private Process GetShortestRemainingTime() {
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
            Process currentProcess = GetShortestRemainingTime();
            currentProcess.ExecutePartly(1);
            tick++;
            
            if (currentProcess.IsCompleted) {
                ExecutedProcesses.Add(currentProcess);
                processList.Remove(currentProcess);
            }

            var restProcesses = processList.Where(p => p.ArrivalTime <= tick);

            foreach (var process in restProcesses) {
                if (process == currentProcess) {
                    continue;
                }
                process.AddWaitingTime(1);
            }
        }
    }
}