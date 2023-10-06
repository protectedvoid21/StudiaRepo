namespace SO3.Algorithms; 

public class RANDAlgorithm : Algorithm {
    private readonly Random random;
    
    public RANDAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
        random = new Random();
    }

    protected override Page GetAvailablePage(int request) {
        foreach (var page in pages) {
            if (page.Request == request) {
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                return page;
            }
        }

        FailureCount++;
        int randomPageIndex = random.Next(pages.Length);
        return pages[randomPageIndex];
    }
}