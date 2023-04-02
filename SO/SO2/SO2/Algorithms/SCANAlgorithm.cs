namespace SO2.Algorithms; 

public class SCANAlgorithm : Algorithm {
    private readonly int cylinderCount;
    private bool goingRight = true;
    
    public SCANAlgorithm(List<Request> requestList, string name, int cylinderCount) : base(requestList, name) {
        this.cylinderCount = cylinderCount;
    }

    private Queue<Request> GetRequestQueue() {
        IEnumerable<Request> requests = GetAvailableForDirection();
        if (goingRight) {
            requests = requests.OrderBy(r => r.Cylinder);
        }
        else {
            requests = requests.OrderByDescending(r => r.Cylinder);
        }
        
        if (headPosition != cylinderCount) {
            tick += cylinderCount - headPosition;
        }
        else {
            tick += Math.Abs(headPosition - cylinderCount);
        }

        return new Queue<Request>(requests);
    }

    private List<Request> GetAvailableForDirection() {
        List<Request> available = new();

        foreach (var request in requestList) {
            if (request.ArrivalTime > tick + cylinderCount) {
                return available;
            }

            if (goingRight) {
                if (tick + request.Cylinder - headPosition + 1 >= request.ArrivalTime) {
                    available.Add(request);
                }
            }
            else {
                if (tick - request.Cylinder + cylinderCount + 1 >= request.ArrivalTime) {
                    available.Add(request);
                }
            }
        }

        return available;
    }

    public override void Execute() {
        while (requestList.Count > 0) {
            var requestQueue = GetRequestQueue();
            
            foreach (var request in requestQueue) {
                request.AddWaitingTime(request.Cylinder - 1);
            }

            while (requestQueue.Count > 0) {
                Request currentRequest = requestQueue.Dequeue();

                MoveHeadToRequest(currentRequest);
                RemoveRequest(currentRequest);
            }
            
            if (requestList.Count == 0) {
                break;
            }

            int endCylinder = goingRight ? cylinderCount : 1;

            MoveHeadToRequest(new Request(endCylinder, 0));
            AddWaitingTimeToRest();
            goingRight = !goingRight;
        }
    }
}