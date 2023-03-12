namespace SO1.Algorithms;

public class FCFSAlgorithm : IAlgorithm {
    private List<Process> processList;
    private List<Process> executedProcesses;

    public FCFSAlgorithm(List<Process> processList) {
        this.processList = processList;
        executedProcesses = new();
    }

    public void Execute() {
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

            executedProcesses.Add(process);
            processList.Remove(process);
        }

        Console.WriteLine($"Średni czas oczekiwania dla FCFS : {(float)executedProcesses.Sum(p => p.WaitingTime) / executedProcesses.Count}");
    }
}