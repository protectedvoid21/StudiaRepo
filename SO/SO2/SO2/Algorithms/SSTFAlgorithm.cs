namespace SO2.Algorithms; 

public class SSTFAlgorithm : Algorithm {
    public SSTFAlgorithm(List<Request> requestList, string name) : base(requestList, name) {
    }
    
    public override void Execute() {
        while (requestList.Count > 0) {
            var requestsAvailable = GetAvailableRequests();

            if (!requestsAvailable.Any()) {
                int missingTicks = requestList.Min(r => r.ArrivalTime) - tick;
                tick += missingTicks;
                continue;
            }

            Request currentRequest = requestsAvailable.MinBy(r => GetRequestDistance(r));

            int currentHeadMove = MoveHeadToRequest(currentRequest);
            currentRequest.AddWaitingTime(currentHeadMove);
            tick += currentHeadMove;
            
            RemoveRequest(currentRequest);

            AddWaitingTimeToRest();
        }
    }
}