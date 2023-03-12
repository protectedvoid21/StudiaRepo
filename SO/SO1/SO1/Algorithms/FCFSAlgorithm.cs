namespace SO1.Algorithms;

public class FCFSAlgorithm : IAlgorithm {
    private IEnumerable<Process> processList;

    public FCFSAlgorithm(IEnumerable<Process> processList) {
        this.processList = processList;
    }

    public void Execute() {
        int tick = 1;

        processList = processList.OrderBy(p => p.ArrivalTime);

        while(!processList.All(p => p.IsCompleted)) {
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

            //Console.WriteLine(process.WaitingTime);
        }

        Console.WriteLine($"Średni czas oczekiwania dla FCFS : {(float)processList.Sum(p => p.WaitingTime) / processList.Count()}");
    }
}