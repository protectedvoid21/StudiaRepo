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

        headPosition = requestList[0].Cylinder;
    }
    
    public abstract void Execute();

    protected List<Request> GetAvailableRequests(int tick) {
        List<Request> available = new();

        foreach (var request in requestList) {
            if (request.ArrivalTime > tick) {
                return available;
            }
            available.Add(request);
        }

        return available;
    }

    protected void AddWaitingTimeToRest(int tick) {
        List<Request> awaiting = new();

        foreach (var request in requestList) {
            if (request.ArrivalTime >= tick) {
                return;
            }
            request.AddWaitingTime(tick - request.ArrivalTime - (int)request.WaitingTime);
        }
    }
    
    protected void RemoveRequest(Request request) {
        requestList.Remove(request);
        executedRequest.Add(request);
    }

    protected int GetRequestDistance(Request request) {
        return Math.Abs(request.Cylinder - headPosition);
    }

    protected int MoveHeadToRequest(Request currentRequest) {
        int headCurrentMove = GetRequestDistance(currentRequest);
        HeadMoves += (ulong)headCurrentMove;
        headPosition = currentRequest.Cylinder;

        return headCurrentMove;
    }
}