namespace SO5.Algorithms;

public class StrategySecond : Algorithm {
    public StrategySecond(AlgorithmData data, string name, int threshold) : base(data, name, threshold) { }
    
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