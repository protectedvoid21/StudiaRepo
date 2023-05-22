namespace SO4.Algorithms; 

public class RegionAlgorithm : ProportionalAlgorithm {
    private readonly float minFaultFrequencyThreshold;
    private readonly float maxFaultFrequencyThreshold;
    private readonly int faultWaitingTime;
    
    public RegionAlgorithm(AlgorithmData data, string name) : base(data, name) {
    }

    protected override void SetProcessesPages() {
        
    }
}