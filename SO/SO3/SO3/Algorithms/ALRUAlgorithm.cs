namespace SO3.Algorithms; 

public class ALRUAlgorithm : Algorithm {
    private Queue<Page> nextPageQueue;

    public ALRUAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
        nextPageQueue = new Queue<Page>();
    }

    protected override Page GetAvailablePage(int request) {
        foreach (var page in pages) {
            if (page.Request == request) {
                return page;
            }
            if (page.IsEmpty) {
                FailureCount++;
                nextPageQueue.Enqueue(page);
                return page;
            }
        }
        
        FailureCount++;
        foreach (var page in nextPageQueue) {
            if (!page.HasSecondChance) {
                nextPageQueue.Enqueue(nextPageQueue.Peek());
                return nextPageQueue.Dequeue();
            }
            page.RemoveSecondChance();
        }

        return nextPageQueue.Dequeue();
    }
}