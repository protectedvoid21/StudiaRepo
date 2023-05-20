namespace SO4; 

public class Process {
    public List<int> RequestList { get; init; }

    public Process(List<int> requestList) {
        RequestList = requestList;
    }
}