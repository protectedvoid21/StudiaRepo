namespace SO1.Algorithms;

public class FCFSAlgorithm : Algorithm {
    public FCFSAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    public override void Execute() {
        int tick = 1;

        processList = processList.OrderBy(p => p.ArrivalTime).ToList();

        while(processList.Any()) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted);
            if(!currentProcesses.Any()) {
                tick++;
                continue;
            }

            Process process = currentProcesses.First();
            process.Execute();

            tick += process.InitialAmount;
            currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted);
            foreach(var proc in currentProcesses) {
                proc.AddWaitingTime(tick - proc.ArrivalTime - proc.WaitingTime);
            }

            ExecutedProcesses.Add(process);
            processList.Remove(process);
        }
    }
}