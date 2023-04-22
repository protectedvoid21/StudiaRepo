using SO3.Algorithms;

namespace SO3; 

public class AlgorithmStats {
    public string Name { get; }
    public int FailureCount { get; }

    public AlgorithmStats(Algorithm algorithm) {
        Name = algorithm.Name;
        FailureCount = algorithm.FailureCount;
    }
}