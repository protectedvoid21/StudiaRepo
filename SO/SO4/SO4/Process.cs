namespace SO4; 

public class Process {
    public Queue<int> RequestQueue { get; init; }
    public List<Page> Pages { get; set; } = new();
    public int FailureCount { get; private set; }
    public int MemorySize => RequestQueue.Distinct().Count();

    public Process(Queue<int> requestQueue) {
        RequestQueue = requestQueue;
    }
    
    private Page GetAvailablePage(int request) {
        Page nonUsedLongest = Pages[0];
        
        foreach (var page in Pages) {
            if (page.Request == request) {
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                return page;
            }
            if (page.LastUsed < nonUsedLongest.LastUsed) {
                nonUsedLongest = page;
            }
        }

        FailureCount++;
        return nonUsedLongest;
    }

    public void Execute(int tick) {
        int request = RequestQueue.Dequeue();
        var currentPage = GetAvailablePage(request);
        currentPage.SetReference(request, tick);
    }
}