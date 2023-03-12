namespace SO1.Algorithms;

public class RRAlgorithm : IAlgorithm {
    private readonly int quantum;
    private List<Process> processList;
    private List<Process> executedProcesses; 

    public RRAlgorithm(List<Process> processList, int quantum) {
        this.processList = processList;
        executedProcesses = new();
        this.quantum = quantum;
    }

    public void Execute() {
        int tick = 1;

        processList = processList.OrderBy(p => p.ArrivalTime).ToList();

        while (processList.Any()) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick);
            if(!currentProcesses.Any()) {
                tick++;
                continue;
            }


            List<Process> completedList = new();
            foreach (var process in currentProcesses) {
                int burnt = process.ExecutePartly(quantum);
                tick += burnt;
                if (process.IsCompleted) {
                    completedList.Add(process);
                }

                var otherProcesses = processList.Where(p => p.ArrivalTime <= tick);
                foreach (var other in otherProcesses) {
                    if (process == other) {
                        continue;
                    }

                    int waitingTime = tick - other.ArrivalTime < burnt ? tick - other.ArrivalTime : burnt;
                    other.AddWaitingTime(waitingTime);
                }
            }

            foreach (var process in completedList) {
                executedProcesses.Add(process);
                processList.Remove(process);
            }
        }
        

        //foreach (var process in processList) {
        //    Console.WriteLine($"{process.InitialAmount} - Waited : {process.WaitingTime}");
        //}

        Console.WriteLine($"Średni czas oczekiwania dla RR (kwant : {quantum}) : {(float)executedProcesses.Sum(p => p.WaitingTime) / executedProcesses.Count}");
    }
}