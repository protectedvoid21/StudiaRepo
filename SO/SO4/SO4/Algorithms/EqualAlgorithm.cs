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

    public override void Execute() {
        base.Execute();
        
        while (tick < tickCount) {
            tick++;
            var recentlyCompletedProcesses = new List<Process>();
            foreach (var process in processList) {
                process.Execute(tick);
                if (process.RequestQueue.Count == 0) {
                    recentlyCompletedProcesses.Add(process);
                    CompletedProcesses.Add(process);
                }
            }

            foreach (var process in recentlyCompletedProcesses) {
                processList.Remove(process);
            }
        }
    }
}