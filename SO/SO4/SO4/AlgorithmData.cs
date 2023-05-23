namespace SO4;

public record AlgorithmData(List<Page> Pages, List<Process> ProcessList) {
    public AlgorithmData GetCopy() {
        var pagesCopy = new List<Page>();
        for (int i = 0; i < Pages.Count; i++) {
            pagesCopy.Add(new Page());
        }

        var processesCopy = new List<Process>();

        foreach (var process in ProcessList) {
            int[] requestArray = new int[process.RequestQueue.Count];
            process.RequestQueue.CopyTo(requestArray, 0);
            processesCopy.Add(new Process(new Queue<int>(requestArray)));
        }

        return new AlgorithmData(pagesCopy, processesCopy);
    }
}

public record AlgorithmInitData(List<AlgorithmStats> AlgorithmStats, int ProcessCount, int PageCount, int MaxRequest);