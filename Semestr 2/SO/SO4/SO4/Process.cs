namespace SO4; 

public class Process {
    public Queue<int> RequestQueue { get; init; }
    public readonly List<Page> Pages = new();
    
    public int FailureCount { get; private set; }
    public int MemorySize => RequestQueue.Distinct().Count();
    public bool IsPaused { get; set; }
    
    private readonly Queue<bool> faultQueue = new();

    public Process(Queue<int> requestQueue) {
        RequestQueue = requestQueue;
    }
    
    public float GetPageFaultFrequency(int faultTimeSpan) => (float)faultQueue.TakeLast(faultTimeSpan).Count(f => f) / faultTimeSpan;

    public int GetWorkingSetSize(int faultTimeSpan) => faultQueue.TakeLast(faultTimeSpan).Count(f => f);
    
    private Page GetAvailablePage(int request) {
        Page longestUnused = Pages[0];
        
        foreach (var page in Pages) {
            if (page.Request == request) {
                faultQueue.Enqueue(false);
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                faultQueue.Enqueue(true);
                return page;
            }
            if (page.LastUsed < longestUnused.LastUsed) {
                longestUnused = page;
            }
        }

        FailureCount++;
        faultQueue.Enqueue(true);
        return longestUnused;
    }

    public void Execute(int tick) {
        if (IsPaused) {
            return;
        }
        
        int request = RequestQueue.Dequeue();
        var currentPage = GetAvailablePage(request);
        currentPage.SetReference(request, tick);
    }

    public Page RemovePage() {
        Page longestUnused = Pages[0];

        foreach (var page in Pages) {
            if (page.LastUsed < longestUnused.LastUsed) {
                longestUnused = page;
            }
            if (page.IsEmpty) {
                return page;
            }
        }
        longestUnused.SetReference(0, 0);
        return longestUnused;
    }

    public Page[] FreePages() {
        var freedPages = new Page[Pages.Count];

        for (int i = 0; i < Pages.Count; i++) {
            Pages[i].SetReference(0, 0);
            freedPages[i] = Pages[i];
        }
        Pages.Clear();

        return freedPages;
    }
}