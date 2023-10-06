namespace SO3.Algorithms; 

public class OPTAlgorithm : Algorithm {
    public OPTAlgorithm(Page[] pages, int[] requests, string name) : base(pages, requests, name) {
    }

    private int GetNextRequestTime(int request) {
        for (int i = tick; i < requests.Length; i++) {
            if (requests[i] == request) {
                return i - tick;
            }
        }
        return -1;
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
        Page furthestPage = pages[0];
        foreach (var page in pages) {
            int currentDistance = GetNextRequestTime(page.Request);
            if (currentDistance == -1) {
                return page;
            }
            if (currentDistance > GetNextRequestTime(furthestPage.Request)) {
                furthestPage = page;
            }
        }

        return furthestPage;
    }
}