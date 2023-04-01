namespace SO2.Algorithms;

public abstract class Algorithm {
    public string Name { get; }
    
    protected List<Request> requestList;
    public List<Request> executedRequest { get; } = new();
    public ulong HeadMoves { get; private set; }
    
    protected int headPosition;

    private readonly int cylinderCount;

    protected Algorithm(List<Request> requestList, string name, int cylinderCount) {
        this.requestList = requestList;
        Name = name;
        this.cylinderCount = cylinderCount;
    }
    
    public abstract void Execute();

    protected void RemoveRequest(Request request) {
        requestList.Remove(request);
        executedRequest.Add(request);
    }

    protected int MoveHeadToRequest(Request currentRequest) {
        int headCurrentMove = Math.Abs(currentRequest.Cylinder - headPosition);
        HeadMoves += (ulong)headCurrentMove;
        headPosition = currentRequest.Cylinder;

        return headCurrentMove;
    }
}