namespace SO2.Algorithms; 

public class SSTFAlgorithm : Algorithm {
    public SSTFAlgorithm(List<Request> requestList, string name, int cylinderCount) : base(requestList, name, cylinderCount) {
    }

    public override void Execute() {
        int tick = 0;

        while (requestList.Count > 0) {
            var requestsAvailable = requestList.Where(r => r.ArrivalTime <= tick);

            
        }
    }
}