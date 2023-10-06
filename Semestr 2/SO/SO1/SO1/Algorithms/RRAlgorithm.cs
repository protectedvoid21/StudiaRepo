namespace SO1.Algorithms;

public class RRAlgorithm : Algorithm {
    private readonly int quantum;

    public RRAlgorithm(List<Process> processList, string name, int quantum) : base(processList, name) {
        Name = $"RR (q = {quantum})";
        this.quantum = quantum;
    }

    public override void Execute() {
        int tick = 1;

        while (processList.Count > 0) {
            if(Utils.IsAnyProcessWaiting(processList, tick) == false) {
                tick++;
                continue;
            }

            var currentProcesses = processList.Where(p => p.ArrivalTime <= tick);
            
            List<Process> completedList = new();
            foreach (var process in currentProcesses) {
                int burnt = process.ExecutePartly(quantum);
                tick += burnt;
                ChangeCount++;

                if (process.IsCompleted) {
                    completedList.Add(process);
                }

                var otherProcesses = processList.Where(p => p.ArrivalTime <= tick && !p.IsCompleted);
                foreach (var other in otherProcesses) {
                    if (process == other) {
                        continue;
                    }

                    int waitingTime = tick - other.ArrivalTime < burnt ? tick - other.ArrivalTime : burnt;
                    other.AddWaitingTime(waitingTime);
                }
            }

            foreach (var process in completedList) {
                ExecutedProcesses.Add(process);
                processList.Remove(process);
            }
        }
    }
}