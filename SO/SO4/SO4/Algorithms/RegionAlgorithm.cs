namespace SO4.Algorithms;

//TODO Odpauzowanie zapauzowanych procesów XDD
public class RegionAlgorithm : EqualAlgorithm {
    private readonly float minFaultFrequencyThreshold;
    private readonly float maxFaultFrequencyThreshold;
    private readonly int faultWaitingTime;
    private readonly int wssInterval;

    private readonly List<Page> freePages = new();
    private readonly IPauseAlgorithmStrategy pauseStrategy;
    
    public RegionAlgorithm(
        AlgorithmData data, 
        string name, 
        float minFaultFrequencyThreshold,
        float maxFaultFrequencyThreshold, 
        int faultWaitingTime, 
        int checkIntervalPercentage,
        IPauseAlgorithmStrategy pauseStrategy) : base(data, name) {
        this.minFaultFrequencyThreshold = minFaultFrequencyThreshold;
        this.maxFaultFrequencyThreshold = maxFaultFrequencyThreshold;
        this.faultWaitingTime = faultWaitingTime;
        this.pauseStrategy = pauseStrategy;
        wssInterval = Math.Clamp((int)(faultWaitingTime * ((float)checkIntervalPercentage / 100)), 1, faultWaitingTime);
    }

    private void DistributePagesByWSS() {
        int requiredPages = processList.Sum(p => p.GetWorkingSetSize(faultWaitingTime));
        
        if (requiredPages > freePages.Count) {
            var pausedProcess = pauseStrategy.PauseProcess(processList);
            pausedProcess.IsPaused = true;
            freePages.AddRange(pausedProcess.FreePages());
            
            AlgorithmHelper.DistributeProportionally(processList, freePages);
            return;
        }

        int pageIndex = 0;
        foreach (var process in processList) {
            if (process.IsPaused) {
                continue;
            }
            while (process.GetWorkingSetSize(faultWaitingTime) > process.Pages.Count) {
                process.Pages.Add(freePages[pageIndex]);
                pageIndex++;
            }
        }
    }

    public override void Execute() {
        SetProcessesPages();
        
        while (tick < tickCount) {
            tick++;
            if (tick % wssInterval == 0) {
                DistributePagesByWSS();
            }
            
            var recentlyCompletedProcesses = new List<Process>();
            foreach (var process in processList) {
                process.Execute(tick);
                
                if (process.RequestQueue.Count == 0) {
                    freePages.AddRange(process.FreePages());
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