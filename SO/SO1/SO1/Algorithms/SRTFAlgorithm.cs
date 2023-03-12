namespace SO1.Algorithms;

public class SRTFAlgorithm : Algorithm {
    public SRTFAlgorithm(List<Process> processList, string name) : base(processList, name) {
    }

    public override void Execute() {
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

            currentProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted).ToArray();

            for(int i = 1; i < currentProcesses.Length; i++) {
                currentProcesses[i].AddWaitingTime(1);
            }

            if (process.IsCompleted) {
                ExecutedProcesses.Add(process);
                processList.Remove(process);
            }
        }
    }
}