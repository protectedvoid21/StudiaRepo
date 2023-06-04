namespace SO5.Algorithms; 

public class StrategyThird : Algorithm {
    private int _transferPercentage;
    private int _minThreshold;

    public StrategyThird(AlgorithmData data, string name, int threshold, int minThreshold, int transferPercentage) : base(data, name,
        threshold) {
        _transferPercentage = transferPercentage;
        _minThreshold = minThreshold;
    }

    private void DistributeFromLightToOverloaded() {
        foreach (var processor in Processors) {
            if (processor.AskForUsage() < _minThreshold) {
                var overloadedProcessor = Processors.FirstOrDefault(p => p.AskForUsage() > _threshold);
                if (overloadedProcessor == null) {
                    return;
                }
                
                overloadedProcessor.TransferRequests(processor, _transferPercentage);
            }
        }
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
            
            int sourceId = request.ProcessorId;
            if(Processors[sourceId].AskForUsage() <= _threshold) {
                Processors[sourceId].AddRequest(request.Amount);

                foreach (var processor in Processors) {
                    processor.Execute();
                }
                continue;
            }

            var restIds = GetRestIds(sourceId);

            bool found = false;
            while (restIds.Count > 0) {
                var foundProcess = Processors[GetRandomProcessId(restIds)];

                if (foundProcess.AskForUsage() <= _threshold) {
                    foundProcess.AddRequest(request.Amount);
                    found = true;
                    break;
                }
            }

            if (!found) {
                Processors[sourceId].AddRequest(request.Amount);
            }
            
            DistributeFromLightToOverloaded();
            
            foreach(var processor in Processors) {
                processor.Execute();
            }
        }
    }
}