namespace SO4.Algorithms; 

public class EqualAlgorithm : Algorithm {
    public EqualAlgorithm(AlgorithmData data, string name) : base(data, name) {
    }
    
    protected override void SetProcessesPages() {
        int pagesPerProcess = pages.Length / processList.Count;
        int restPages = pages.Length % processList.Count;

        int pageIndex = 0;
        foreach (var process in processList) {
            for (int j = 0; j < pagesPerProcess; j++) {
                process.Pages.Add(pages[pageIndex]);
                pageIndex++;
            }

            if (restPages > 0) {
                process.Pages.Add(pages[pageIndex]);
                pageIndex++;
                restPages--;
            }
        }
    }
}