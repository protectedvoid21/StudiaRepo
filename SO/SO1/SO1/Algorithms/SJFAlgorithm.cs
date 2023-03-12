namespace SO1.Algorithms;

public class SJFAlgorithm : IAlgorithm {
    private IEnumerable<Process> processList;

    public SJFAlgorithm(IEnumerable<Process> processList) {
        this.processList = processList;
    }

    public void Execute() {
        int tick = 1;

        while(!processList.All(p => p.IsCompleted)) {
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

            //Console.WriteLine(process.WaitingTime);
        }

        Console.WriteLine($"Średni czas oczekiwania dla SJF : {(float)processList.Sum(p => p.WaitingTime) / processList.Count()}");
    }
}