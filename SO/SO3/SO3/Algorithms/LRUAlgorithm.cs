namespace SO3.Algorithms; 

public class LRUAlgorithm : Algorithm {
    public LRUAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
    }

    protected override Page GetAvailablePage(int request) {
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
}