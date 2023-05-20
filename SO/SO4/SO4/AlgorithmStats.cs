using SO4.Algorithms;

namespace SO4; 

public class AlgorithmStats {
    public string Name { get; }
    public float FailureStandardDeviation { get; }
    public float ProcessFailuresMedian { get; }
    public float ProcessFailuresMean { get; }
    public int FailuresSum { get; }

    public AlgorithmStats(Algorithm algorithm) {
        Name = algorithm.Name;
        FailuresSum = algorithm.CompletedProcesses.Sum(p => p.FailureCount);
        ProcessFailuresMean = (float)algorithm.CompletedProcesses.Average(p => p.FailureCount);
        ProcessFailuresMedian = algorithm.CompletedProcesses.Select(p => p.FailureCount).Median();
        FailureStandardDeviation = algorithm.CompletedProcesses.Select(p => p.FailureCount).StandardDeviation();
    }
}