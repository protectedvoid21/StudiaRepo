namespace SO5;

public class Processor {
    public List<int> LoadHistory { get; } = new();
    
    public int AskedCount { get; private set; }
    public int OverloadCount { get; private set; }
    
    private int _usage;
    private int _threshold;
    
    public void Execute() {
        LoadHistory.Add(_usage);
        if (_usage > _threshold) {
            OverloadCount++;
        }

        if (_usage > 0) {
            _usage--;
        }
    }

    public void AddRequest(int request) {
        _usage += request;
    }

    public void TransferRequests(Processor processor, int amount) {
        _usage -= amount;
        processor.AddRequest(amount);
    }

    public int AskForUsage() {
        AskedCount++;
        return _usage;
    }
}