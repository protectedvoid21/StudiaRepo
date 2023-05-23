namespace SO4.Algorithms;

public class RegionAlgorithm : ProportionalAlgorithm {
    private readonly float minFaultFrequencyThreshold;
    private readonly float maxFaultFrequencyThreshold;
    private readonly int faultWaitingTime;
    private readonly int wssInterval;

    private List<Page> freePages = new();
    
    public RegionAlgorithm(AlgorithmData data, string name, float minFaultFrequencyThreshold,
        float maxFaultFrequencyThreshold, int faultWaitingTime, int checkIntervalPercentage) : base(data, name) {
        this.minFaultFrequencyThreshold = minFaultFrequencyThreshold;
        this.maxFaultFrequencyThreshold = maxFaultFrequencyThreshold;
        this.faultWaitingTime = faultWaitingTime;
        wssInterval = Math.Clamp((int)(faultWaitingTime * ((float)checkIntervalPercentage / 100)), 1, faultWaitingTime);
    }
    
    protected override void SetProcessesPages() {
        const int pagesPerProcess = 2;

        int pageIndex = 0;
        foreach (var process in processList) {
            for (int j = 0; j < pagesPerProcess; j++) {
                process.Pages.Add(pages[pageIndex]);
                pageIndex++;
            }
        }
    }

    private void DistributePagesByWSS() {
        
    }

    public override void Execute() {
        while (tick < tickCount) {
            tick++;
            if (tick % wssInterval == 0) {
                DistributePagesByWSS();
            }
            
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