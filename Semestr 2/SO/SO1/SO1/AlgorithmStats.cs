using SO1.Algorithms;

namespace SO1; 

public class AlgorithmStats {
    public int MinWaiting { get; init; }
    public int MaxWaiting { get; init; }
    public double AverageExecution { get; init; }
    public int BiggestProcess { get; init; }
    public int SmallestProcess { get; init; }
    public double AverageProcessSize { get; init; }
    public int ProcessCount { get; init; }
    public int ChangeCount { get; init; }

    public string Name { get; init; }

    public AlgorithmStats(Algorithm algorithm) {
        var executionProcesses = algorithm.ExecutedProcesses;

        MinWaiting = executionProcesses.Min(p => p.WaitingTime);
        MaxWaiting = executionProcesses.Max(p => p.WaitingTime);
        AverageExecution = executionProcesses.Average(p => p.WaitingTime);
        ProcessCount = executionProcesses.Count;
        SmallestProcess = executionProcesses.Min(p => p.InitialAmount);
        BiggestProcess = executionProcesses.Max(p => p.InitialAmount);
        AverageProcessSize = executionProcesses.Average(p => p.InitialAmount);
        ChangeCount = algorithm.ChangeCount;

        Name = algorithm.Name;
    }
}