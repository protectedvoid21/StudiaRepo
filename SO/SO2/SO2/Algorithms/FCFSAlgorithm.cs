namespace SO2.Algorithms; 

public class FCFSAlgorithm : Algorithm {
    public FCFSAlgorithm(List<Request> requestList, int cylinderCount) : base(requestList, cylinderCount) {
    }

    public override void Execute() {
        int tick = 0;
        requestList = requestList.OrderBy(r => r.ArrivalTime).ToList();

        while (requestList.Count > 0) {
            Request currentRequest = requestList[0];

            if (tick < currentRequest.ArrivalTime) {
                tick += currentRequest.ArrivalTime - tick;
            }

            int headCurrentMove = Math.Abs(currentRequest.Cylinder - headPosition);
            HeadMoves += (ulong)headCurrentMove;
            headPosition = currentRequest.Cylinder;

            RemoveRequest(currentRequest);
            tick += headCurrentMove;

            var restRequests = requestList.Where(r => r.ArrivalTime < tick);
            foreach (var request in restRequests) {
                request.AddWaitingTime(tick - currentRequest.ArrivalTime - currentRequest.WaitingTime);
            }
        }
    }
}