namespace SO1.Algorithms;

public class SRTFAlgorithm : IAlgorithm {
    private List<Process> processList;

    public SRTFAlgorithm(List<Process> processList) {
        this.processList = processList;
    }

    public void Execute() {
        int tick = 1;

        while(processList.Exists(p => !p.IsCompleted)) {
            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted).OrderBy(p => p.Amount).ToArray();
            if(currentProcesses.Length == 0) {
                tick++;
                continue;
            }

            Process process = currentProcesses[0];
            process.ExecutePartly(1);
            tick++;

            currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted).ToArray();

            for(int i = 1; i < currentProcesses.Length; i++) {
                currentProcesses[i].AddWaitingTime(1);
            }
        }
        //foreach (var process in processList) {
        //    Console.WriteLine($"{process.InitialAmount} - Waited : {process.WaitingTime}");
        //}

        Console.WriteLine($"Średni czas oczekiwania dla SRTF : {(float)processList.Sum(p => p.WaitingTime) / processList.Count}");
    }
}