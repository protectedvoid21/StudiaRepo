namespace SO5.Algorithms;

public abstract class Algorithm {
    public string Name { get; init; }
    public int MigrationCount { get; protected set; }
    public Processor[] Processors { get; }
    protected readonly List<Request> _requests;
    private Random random = new();
    
    protected int _threshold;

    protected Algorithm(AlgorithmData data, string name, int threshold) {
        Name = name;
        Processors = data.Processors;
        _requests = data.Requests;
        _threshold = threshold;
    }

    protected int GetRandomProcessId(List<int> restIds) {
        if (restIds.Count == 0) {
            return -1;
        }
        
        var randomId = random.Next(0, restIds.Count);
        restIds.Remove(restIds[randomId]);
        
        return randomId;
    }

    protected List<int> GetRestIds(int exceptId) {
        var restIds = new List<int>();
        for (var i = 0; i < Processors.Length; i++) {
            if (i == exceptId) {
                continue;
            }
            restIds.Add(i);
        }

        return restIds;
    }

    public abstract void Execute();
}