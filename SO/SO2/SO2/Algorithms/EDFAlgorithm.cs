namespace SO2.Algorithms; 

public class EDFAlgorithm : Algorithm {
    public EDFAlgorithm(List<Request> requestList, string name) : base(requestList, name) {
    }

    private void RemoveFailedRequests(IEnumerable<Request> deadlines, Request current) {
        foreach (var request in deadlines) {
            if (request == current) {
                continue;
            }
            if (request.RestDeadline < 0) {
                RemoveRequest(request);
            }
        }
    }

    public override void Execute() {
        while (requestList.Count > 0) {
            var requestsAvailable = GetAvailableRequests();

            if (!requestsAvailable.Any()) {
                int missingTicks = requestList.Min(r => r.ArrivalTime) - tick;
                tick += missingTicks;
                continue;
            }

            var deadlineRequests = requestsAvailable.Where(r => r.IsDeadline);
            Request currentRequest;
            int currentHeadMove;
            
            if (deadlineRequests.Any()) {
                currentRequest = deadlineRequests.MinBy(r => r.ArrivalTime);

                if (GetRequestDistance(currentRequest) > currentRequest.RestDeadline) {
                    int newHeadPos = currentRequest.Cylinder > headPosition
                        ? headPosition + currentRequest.RestDeadline
                        : headPosition - currentRequest.RestDeadline;
                    
                    currentHeadMove = MoveHeadToRequest(new Request(newHeadPos, 0));
                }
                else {
                    currentHeadMove = MoveHeadToRequest(currentRequest);
                    currentRequest.MarkAsHandled();
                }
            }
            else {
                currentRequest = requestsAvailable.MinBy(r => GetRequestDistance(r));
                currentHeadMove = MoveHeadToRequest(currentRequest);
            }

            currentRequest.AddWaitingTime(currentHeadMove);
            tick += currentHeadMove;
            
            RemoveRequest(currentRequest);
            AddWaitingTimeToRest();
            RemoveFailedRequests(deadlineRequests, currentRequest);
        }
    }
}