namespace SO2; 

public class Request {
    public int Cylinder { get; init; }
    public int ArrivalTime { get; init; }
    public int WaitingTime { get; private set; }

    public Request(int cylinder, int arrivalTime) {
        Cylinder = cylinder;
        ArrivalTime = arrivalTime;
    }

    public void AddWaitingTime(int time) {
        WaitingTime += time;
    }
}