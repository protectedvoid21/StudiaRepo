using SO5.Algorithms;

namespace SO5;

public record AlgorithmStats {
    public string Name { get; }
    public double AverageProcessorLoad { get; }
    public double AverageLoadDeviation { get; }
    public int AskedCount { get; }
    public int OverloadCount { get; }
    public int MigrationCount { get; }

    public AlgorithmStats(Algorithm algorithm) {
        Name = algorithm.Name;
    
        var processors = algorithm.Processors;
        AverageProcessorLoad = processors.Average(p => p.LoadHistory.Average());
        AverageLoadDeviation = processors.Average(p => p.LoadHistory.Select(l => Math.Abs(l - AverageProcessorLoad)).Average());
        AskedCount = processors.Sum(p => p.AskedCount);
        OverloadCount = processors.Sum(p => p.OverloadCount);
        MigrationCount = -1;
    }
}