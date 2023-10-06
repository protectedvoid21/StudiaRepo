using SO2.Algorithms;

namespace SO2;

public class AlgorithmDeadlineStats {
    public string Name { get; }
    public ulong HeadMoves { get; }
    public int DeadlineCount { get; }
    public int UnachievedDeadlines { get; }
    public int RequestCount { get; }

    public AlgorithmDeadlineStats(Algorithm algorithm) {
        var executed = algorithm.executedRequest;

        Name = algorithm.Name;
        HeadMoves = algorithm.HeadMoves;
        DeadlineCount = executed.Count(r => r.IsDeadline);
        UnachievedDeadlines = executed.Count(r => r.WasDeadlineHandled == false && r.IsDeadline);
        RequestCount = executed.Count;
    }
}