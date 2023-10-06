namespace SO1.Algorithms;

public class FCFSAlgorithm : Algorithm {
    public FCFSAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    public override void Execute() {
        int tick = 1;

        while(processList.Count > 0) {
            if(Utils.IsAnyProcessWaiting(processList, tick) == false) {
                tick++;
                continue;
            }

            Process currentProcess = processList[0];
            currentProcess.Execute();
            ChangeCount++;

            tick += currentProcess.InitialAmount;
            
            var restProcesses = processList.Where(p => p.ArrivalTime <= tick);
            foreach(var proc in restProcesses) {
                if (proc == currentProcess) {
                    continue;
                }
                proc.AddWaitingTime(tick - proc.ArrivalTime - proc.WaitingTime);
            }

            ExecutedProcesses.Add(currentProcess);
            processList.Remove(currentProcess);
        }
    }
}