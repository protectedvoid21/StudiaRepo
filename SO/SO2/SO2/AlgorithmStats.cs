using SO2.Algorithms;

namespace SO2; 

public class AlgorithmStats {
    public long MinWaiting { get; }
    public long MaxWaiting { get; }
    public ulong HeadMoves { get; }
    public double AverageWaiting { get; }
    public int RequestCount { get; }
    public int CylinderCount { get; }

    public string Name { get; }

    public AlgorithmStats(Algorithm algorithm) {
        Name = algorithm.Name;

        var executedRequests = algorithm.executedRequest;

        MinWaiting = executedRequests.Min(r => r.WaitingTime);
        MaxWaiting = executedRequests.Max(r => r.WaitingTime);
        HeadMoves = algorithm.HeadMoves;
        RequestCount = executedRequests.Count;
        AverageWaiting = (double)executedRequests.Sum(e => e.WaitingTime) / RequestCount;
    }
}