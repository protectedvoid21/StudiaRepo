namespace SO2.Algorithms; 

public class CSCANAlgorithm : Algorithm {
    private readonly int cylinderCount;
    
    public CSCANAlgorithm(List<Request> requestList, string name, int cylinderCount) : base(requestList, name) {
        this.cylinderCount = cylinderCount;
    }
    
    private Queue<Request> GetRequestQueue() {
        IEnumerable<Request> requests = GetAvailableForDirection();
        requests = requests.OrderBy(r => r.Cylinder);

        if (headPosition == 1) {
            tick += cylinderCount;
        }
        else {
            tick = cylinderCount - headPosition;
        }
        
        return new Queue<Request>(requests);
    }
    
    private List<Request> GetAvailableForDirection() {
        List<Request> available = new();

        foreach (var request in requestList) {
            if (request.ArrivalTime > tick + cylinderCount) {
                return available;
            }
            if (tick + request.Cylinder - headPosition + 1 >= request.ArrivalTime) {
                available.Add(request);
            }
        }

        return available;
    }
    
    private void UpdateQueueWaitingTime(IEnumerable<Request> requests) {
        foreach (var request in requests) {
            if (tick < request.ArrivalTime) {
                request.AddWaitingTime(tick + request.Cylinder - request.ArrivalTime - 1);
            }
            request.AddWaitingTime(request.Cylinder - 1);
        }
    }

    public override void Execute() {
        while (requestList.Count > 0) {
            var requestQueue = GetRequestQueue();
            
            UpdateQueueWaitingTime(requestQueue);

            while (requestQueue.Count > 0) {
                Request currentRequest = requestQueue.Dequeue();

                MoveHeadToRequest(currentRequest);
                RemoveRequest(currentRequest);
            }

            if (requestList.Count == 0) {
                break;
            }
            MoveHeadToRequest(new Request(cylinderCount, 0));
            //MoveHeadToRequest(new Request(1, 0));
            AddWaitingTimeToRest();

            headPosition = 1;
        }
    }
}