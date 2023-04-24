namespace SO3.Algorithms; 

public class ALRUAlgorithm : Algorithm {
    private List<Page> nextPageList;

    public ALRUAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
        nextPageList = new List<Page>();
    }
    
    protected override Page GetAvailablePage(int request) {
        foreach (var page in pages) {
            if (page.Request == request) {
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                nextPageList.Add(page);
                return page;
            }
        }
        
        FailureCount++;
        foreach (var page in nextPageList) {
            if (!page.HasSecondChance) {
                nextPageList.Remove(page);
                nextPageList.Add(page);
                return page;
            }
            page.RemoveSecondChance();
        }

        Page toRemovePage = nextPageList[0];
        nextPageList.Remove(toRemovePage);
        nextPageList.Add(toRemovePage);
        return toRemovePage;
    }
}