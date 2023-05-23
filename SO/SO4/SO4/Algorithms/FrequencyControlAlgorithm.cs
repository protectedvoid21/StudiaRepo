namespace SO4.Algorithms;

public class FrequencyControlAlgorithm : ProportionalAlgorithm {
    private readonly float minFaultFrequencyThreshold;
    private readonly float maxFaultFrequencyThreshold;
    private readonly int faultWaitingTime;

    private List<Page> freePages = new();

    public FrequencyControlAlgorithm(
        AlgorithmData data, string name, float minFaultFrequencyThreshold, float maxFaultFrequencyThreshold,
        int faultWaitingTime) : base(data, name) {
        this.minFaultFrequencyThreshold = minFaultFrequencyThreshold;
        this.maxFaultFrequencyThreshold = maxFaultFrequencyThreshold;
        this.faultWaitingTime = faultWaitingTime;
    }

    private void AdjustProcessPages(Process process) {
        var pageFaultFrequency = process.GetPageFaultFrequency(faultWaitingTime);
        if (pageFaultFrequency < minFaultFrequencyThreshold) {
            if (process.Pages.Count <= 1) {
                return;
            }

            Page removedPage = process.RemovePage();
            removedPage.SetReference(0, 0);
            freePages.Add(removedPage);
        }
        else if (pageFaultFrequency > maxFaultFrequencyThreshold && freePages.Count > 0) {
            process.Pages.Add(freePages[0]);
            freePages.Remove(freePages[0]);
        }
    }

    public override void Execute() {
        SetProcessesPages();

        while (tick < tickCount) {
            tick++;
            var recentlyCompletedProcesses = new List<Process>();
            foreach (var process in processList) {
                process.Execute(tick);
                
                if (process.RequestQueue.Count == 0) {
                    recentlyCompletedProcesses.Add(process);
                    CompletedProcesses.Add(process);
                }
                AdjustProcessPages(process);
            }

            foreach (var process in recentlyCompletedProcesses) {
                processList.Remove(process);
            }
        }
    }
}