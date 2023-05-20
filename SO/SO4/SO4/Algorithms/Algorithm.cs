namespace SO4.Algorithms; 

public abstract class Algorithm {
    public string Name { get; }
    public int FailureCount { get; protected set; }
    protected readonly Page[] pages;
    protected readonly int[] requests;
    protected int tick;

    protected Algorithm(Page[] pages, int[] requests, string name) {
        this.pages = pages;
        this.requests = requests;
        Name = name;
    }

    private Page GetAvailablePage(int request) {
        Page nonUsedLongest = pages[0];
        
        foreach (var page in pages) {
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

    public void Execute() {
        foreach (var request in requests) {
            tick++;
            Page availablePage = GetAvailablePage(request);

            availablePage.SetReference(request, tick);
        }
    }
}