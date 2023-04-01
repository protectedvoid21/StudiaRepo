namespace SO2.Algorithms; 

public class SCANAlgorithm : Algorithm {
    private bool goingRight = true;
    
    public SCANAlgorithm(List<Request> requestList, string name, int cylinderCount) : base(requestList, name, cylinderCount) {
    }

    public override void Execute() {
        int tick = 0;

        while (requestList.Count > 0) {
            
        }
    }
}