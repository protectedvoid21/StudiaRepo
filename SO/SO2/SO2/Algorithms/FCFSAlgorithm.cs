namespace SO2.Algorithms; 

public class FCFSAlgorithm : Algorithm {
    public FCFSAlgorithm(List<Request> requestList, string name, int cylinderCount) : base(requestList, name, cylinderCount) {
    }

    public override void Execute() {
        int tick = 0;
        headPosition = requestList[0].Cylinder;

        while (requestList.Count > 0) {
            Request currentRequest = requestList[0];

            if (tick < currentRequest.ArrivalTime) {
                tick += currentRequest.ArrivalTime - tick;
            }

            int headCurrentMove = MoveHeadToRequest(currentRequest);
            tick += headCurrentMove;

            RemoveRequest(currentRequest);

            var restRequests = requestList.Where(r => r.ArrivalTime < tick);
            foreach (var request in restRequests) {
                request.AddWaitingTime(tick - currentRequest.ArrivalTime - currentRequest.WaitingTime);
            }
        }
    }
}