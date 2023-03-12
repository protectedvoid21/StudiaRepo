namespace SO1; 

public class AlgorithmStats {
    public int MinWaiting { get; init; }
    public int MaxWaiting { get; init; }
    public double AverageExecution { get; init; }
    public int BiggestProcess { get; init; }
    public int SmallestProcess { get; init; }
    public double AverageProcessSize { get; init; }
    public int ProcessCount { get; init; }

    public string Name { get; init; }

    public AlgorithmStats(List<Process> executionProcesses, string algorithmName) {
        MinWaiting = executionProcesses.Min(p => p.WaitingTime);
        MaxWaiting = executionProcesses.Max(p => p.WaitingTime);
        AverageExecution = executionProcesses.Average(p => p.WaitingTime);
        ProcessCount = executionProcesses.Count;
        SmallestProcess = executionProcesses.Min(p => p.InitialAmount);
        BiggestProcess = executionProcesses.Max(p => p.InitialAmount);
        AverageProcessSize = executionProcesses.Average(p => p.InitialAmount);

        Name = algorithmName;
    }
}