namespace SO1.Algorithms;

public class RRAlgorithm : IAlgorithm {
    private readonly int quantum;
    private IEnumerable<Process> processList;

    public RRAlgorithm(IEnumerable<Process> processList, int quantum) {
        this.processList = processList;
        this.quantum = quantum;
    }

    public void Execute() {
        int tick = 1;

        processList = processList.OrderBy(p => p.ArrivalTime);

        while (!processList.All(p => p.IsCompleted)) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted);
            if(!currentProcesses.Any()) {
                tick++;
                continue;
            }

            foreach (var process in currentProcesses) {
                int burnt = process.ExecutePartly(quantum);
                tick += burnt;
                var otherProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted);
                foreach (var other in otherProcesses) {
                    if (process == other) {
                        continue;
                    }

                    int waitingTime = tick - other.ArrivalTime < burnt ? tick - other.ArrivalTime : burnt;
                    other.AddWaitingTime(waitingTime);
                }
            }
        }
        

        //foreach (var process in processList) {
        //    Console.WriteLine($"{process.InitialAmount} - Waited : {process.WaitingTime}");
        //}

        Console.WriteLine($"Średni czas oczekiwania dla RR (kwant : {quantum}) : {(float)processList.Sum(p => p.WaitingTime) / processList.Count()}");
    }
}