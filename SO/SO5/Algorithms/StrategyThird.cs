namespace SO5.Algorithms; 

public class StrategyThird : Algorithm {
    private int _transferPercentage;
    private List<Processor> _freeProcessList = new();

    public StrategyThird(AlgorithmData data, string name, int threshold, int transferPercentage) : base(data, name,
        threshold) {
        _transferPercentage = transferPercentage;
    }
    
    public override void Execute() {
        int tick = 1;

        foreach (var request in _requests) {
            while(request.AppearTime > tick) {
                foreach (var processor in Processors) {
                    processor.Execute();
                }
                tick++;
            }
        }
    }
}