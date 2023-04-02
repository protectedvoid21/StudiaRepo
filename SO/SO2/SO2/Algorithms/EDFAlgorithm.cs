namespace SO2.Algorithms; 

public class EDFAlgorithm : Algorithm {
    public EDFAlgorithm(List<Request> requestList, string name) : base(requestList, name) {
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
                currentRequest = deadlineRequests.MinBy(r => r.InitialDeadline);
                
                if (GetRequestDistance(currentRequest) > currentRequest.RestDeadline) {
                    currentHeadMove = MoveHeadToRequest(new Request(currentRequest.RestDeadline, 0));
                }
                else {
                    currentHeadMove = MoveHeadToRequest(currentRequest);
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
        }
    }
}