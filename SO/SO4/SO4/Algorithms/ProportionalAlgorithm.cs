using System.Diagnostics;

namespace SO4.Algorithms; 

public class ProportionalAlgorithm : Algorithm {
    public ProportionalAlgorithm(AlgorithmData data, string name) : base(data, name) {
    }

    protected override void SetProcessesPages() {
        int memorySum = processList.Sum(p => p.MemorySize);

        int pageIndex = 0;
        decimal processSum = 0;
        
        foreach (var process in processList) {
            decimal previousSum = processSum;
            decimal processNotRounded = (decimal)process.MemorySize / memorySum * pages.Length;
            processSum += processNotRounded;

            int processPages = (int)processSum - (int)previousSum;
        
            for (int i = 0; i < processPages; i++) {
                process.Pages.Add(pages[pageIndex]);
                pageIndex++;
            }
        }

        if (processList.Sum(p => p.Pages.Count) < pages.Length) {
            processList[0].Pages.Add(pages[^1]);
        }
    }
}