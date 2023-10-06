namespace SO2.Algorithms; 

public class FDSCANAlgorithm : Algorithm {
    public FDSCANAlgorithm(List<Request> requestList, string name) : base(requestList, name) {
    }

    private Queue<Request> GetRequestsOnWay(int cylinder) {
        Queue<Request> onWayQueue = new();
        
        if (cylinder == headPosition) {
            return onWayQueue;
        }
        
        bool goingRight = headPosition - cylinder < 0;
        
        foreach (var request in requestList) {
            if (goingRight) {
                if (tick + request.Cylinder - headPosition + 1 >= request.ArrivalTime) {
                    request.AddWaitingTime(tick + request.Cylinder - headPosition + 1);
                    onWayQueue.Enqueue(request);
                }
            }
            else {
                if (tick - request.Cylinder + headPosition + 1 >= request.ArrivalTime) {
                    request.AddWaitingTime(tick - request.Cylinder + headPosition + 1);
                    onWayQueue.Enqueue(request);
                }
            }
        }

        return onWayQueue;
    }

    private void ExecuteFDQueue(Request dest) {
        var onWayRequests = GetRequestsOnWay(dest.Cylinder);

        foreach (var request in onWayRequests) {
            request.AddWaitingTime(Math.Abs(dest.Cylinder - request.Cylinder)); 
        }

        while (onWayRequests.Count > 0) {
            Request currentRequest = onWayRequests.Dequeue();
            if (currentRequest.IsDeadline) {
                currentRequest.MarkAsHandled();
            }
            RemoveRequest(currentRequest);
        }
        
        tick += MoveHeadToRequest(dest);
    }

    private IEnumerable<Request> GetDeadlines(List<Request> available) {
        List<Request> deadlines = new();
        List<Request> unachievable = new();
        
        foreach (var request in available) {
            if (request.IsDeadline) {
                if (Math.Abs(headPosition - request.Cylinder) > request.RestDeadline) {
                    unachievable.Add(request);
                }
                else {
                    deadlines.Add(request);
                }
            }
        }

        foreach (var request in unachievable) {
            RemoveRequest(request);
            available.Remove(request);
        }
        return deadlines;
    }

    public override void Execute() {
        while (requestList.Count > 0) {
            var requestsAvailable = GetAvailableRequests();

            if (!requestsAvailable.Any()) {
                int missingTicks = requestList.Min(r => r.ArrivalTime) - tick;
                tick += missingTicks;
                continue;
            }

            var deadlines = GetDeadlines(requestsAvailable);

            if (requestsAvailable.Count == 0) {
                continue;
            }

            Request currentRequest;

            if (deadlines.Any()) {
                currentRequest = deadlines.MinBy(r => r.RestDeadline);
                currentRequest.MarkAsHandled();
                RemoveRequest(currentRequest);
                ExecuteFDQueue(currentRequest);
            }
            else {
                currentRequest = requestsAvailable.MinBy(r => GetRequestDistance(r));
                int currentHeadMove = MoveHeadToRequest(currentRequest);
                tick += currentHeadMove;
                currentRequest.AddWaitingTime(currentHeadMove);
                RemoveRequest(currentRequest);
            }

            AddWaitingTimeToRest();
        }
    }
}