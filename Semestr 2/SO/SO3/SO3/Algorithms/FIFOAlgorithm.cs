namespace SO3.Algorithms; 

public class FIFOAlgorithm : Algorithm {
    public FIFOAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
    }

    protected override Page GetAvailablePage(int request) {
        Page latestPage = pages[0];
        foreach (var page in pages) {
            if (page.Request == request) {
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                return page;
            }
            if (page.SwitchedTick < latestPage.SwitchedTick) {
                latestPage = page;
            }
        }

        FailureCount++;
        return latestPage;
    }
}