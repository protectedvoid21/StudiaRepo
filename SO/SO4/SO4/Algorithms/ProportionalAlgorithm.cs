using System.Diagnostics;

namespace SO4.Algorithms; 

public class ProportionalAlgorithm : Algorithm {
    public ProportionalAlgorithm(AlgorithmData data, string name) : base(data, name) {
    }

    protected override void SetProcessesPages() {
        AlgorithmHelper.DistributeProportionally(processList, pages);
    }
}