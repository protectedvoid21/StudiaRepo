namespace SO2; 

public class Request {
    public int Cylinder { get; }
    public int ArrivalTime { get; }
    public long WaitingTime { get; private set; }
    
    public int InitialDeadline { get; }
    public int RestDeadline { get; private set; }
    public bool WasDeadlineHandled { get; private set; }

    public bool IsDeadline => InitialDeadline > 0;

    public Request(int cylinder, int arrivalTime, int initialDeadline = 0) {
        Cylinder = cylinder;
        ArrivalTime = arrivalTime;
        InitialDeadline = initialDeadline;
    }

    public void AddWaitingTime(int time) {
        WaitingTime += time;

        if (!IsDeadline) {
            return;
        }
        
        if (RestDeadline < 0) {
            RestDeadline = 0;
            WasDeadlineHandled = false;
        }
        else {
            RestDeadline -= time;
        }
    }
}