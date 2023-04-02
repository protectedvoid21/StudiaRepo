namespace SO2; 

public class RequestDeadline : Request {
    public int InitialDeadline { get; }
    public int RestDeadline { get; private set; }
    public bool WasDeadlineHandled { get; private set; }
    
    public RequestDeadline(int cylinder, int arrivalTime, int initialDeadline) : base(cylinder, arrivalTime) {
        InitialDeadline = initialDeadline;
        RestDeadline = initialDeadline;
    }
    
    public override void AddWaitingTime(int time) {
        base.AddWaitingTime(time);

        RestDeadline -= time;
        if (RestDeadline < 0) {
            WasDeadlineHandled = false;
        }
    }
}