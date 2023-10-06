    namespace SO2.Algorithms; 

public class FCFSAlgorithm : Algorithm {
    public FCFSAlgorithm(List<Request> requestList, string name) : base(requestList, name) {
    }

    public override void Execute() {
        while (requestList.Count > 0) {
            Request currentRequest = requestList[0];

            if (tick < currentRequest.ArrivalTime) {
                tick += currentRequest.ArrivalTime - tick;
            }

            int headCurrentMove = MoveHeadToRequest(currentRequest);
            tick += headCurrentMove;

            currentRequest.AddWaitingTime(headCurrentMove);
            RemoveRequest(currentRequest);

            AddWaitingTimeToRest();
        }
    }
}