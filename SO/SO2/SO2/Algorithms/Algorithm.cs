namespace SO2.Algorithms;

public abstract class Algorithm {
    protected List<Request> requestList;
    public List<Request> executedRequest { get; private set; } = new();
    public ulong HeadMoves { get; protected set; }
    
    protected int headPosition;

    private readonly int cylinderCount;
    
    public Algorithm(List<Request> requestList, int cylinderCount) {
        this.requestList = requestList;
        this.cylinderCount = cylinderCount;
    }
    
    public abstract void Execute();

    protected void RemoveRequest(Request request) {
        requestList.Remove(request);
        executedRequest.Add(request);
    }
}