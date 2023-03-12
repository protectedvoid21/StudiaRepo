namespace SO1.Algorithms;

public class SRTFAlgorithm : IAlgorithm {
    private List<Process> processList;
    private List<Process> executedProcesses;

    public SRTFAlgorithm(List<Process> processList) {
        this.processList = processList;
        executedProcesses = new();
    }

    public void Execute() {
        int tick = 1;

        while(processList.Any()) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick).OrderBy(p => p.Amount).ToArray();
            if(currentProcesses.Length == 0) {
                tick++;
                continue;
            }

            Process process = currentProcesses[0];
            process.ExecutePartly(1);
            tick++;

            currentProcesses = processList.Where(p => p.ArrivalTime <= tick).ToArray();

            for(int i = 1; i < currentProcesses.Length; i++) {
                currentProcesses[i].AddWaitingTime(1);
            }

            if (process.IsCompleted) {
                executedProcesses.Add(process);
                processList.Remove(process);
            }
        }
        //foreach (var process in processList) {
        //    Console.WriteLine($"{process.InitialAmount} - Waited : {process.WaitingTime}");
        //}

        Console.WriteLine($"Średni czas oczekiwania dla SRTF : {(float)executedProcesses.Sum(p => p.WaitingTime) / executedProcesses.Count}");
    }
}