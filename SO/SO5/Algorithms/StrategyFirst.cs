namespace SO5.Algorithms; 

public class StrategyFirst : Algorithm {
    private int _maxAskCount;

    public StrategyFirst(AlgorithmData data, string name, int threshold, int maxAskCount) : base(data, name, threshold) {
        if (data.Processors.Length <= maxAskCount) {
            maxAskCount = data.Processors.Length - 1;
        }
        _maxAskCount = maxAskCount;
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

            var restIds = GetRestIds(sourceId);
            
            bool found = false;
            int askCount = _maxAskCount;
            
            while (restIds.Count > 0 && askCount > 0) {
                Processor foundProcessor = Processors[GetRandomProcessId(restIds)];
                askCount--;
                
                if (foundProcessor.AskForUsage() <= _threshold) {
                    foundProcessor.AddRequest(request.Amount);
                    MigrationCount++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                Processors[sourceId].AddRequest(request.Amount);
            }

            foreach (var processor in Processors) {
                processor.Execute();
            }
        }
    }
}