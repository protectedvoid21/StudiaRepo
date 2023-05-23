namespace SO4; 

public static class AlgorithmHelper {
    public static void DistributeProportionally(List<Process> processList, List<Page> pages) {
        int memorySum = processList.Sum(p => p.MemorySize);

        int pageIndex = 0;
        decimal processSum = 0;
        
        foreach (var process in processList) {
            decimal previousSum = processSum;
            decimal processNotRounded = (decimal)process.MemorySize / memorySum * pages.Count;
            processSum += processNotRounded;

            int processPages = (int)processSum - (int)previousSum;
        
            for (int i = 0; i < processPages; i++) {
                process.Pages.Add(pages[pageIndex]);
                pageIndex++;
            }
        }

        if (processList.Sum(p => p.Pages.Count) < pages.Count) {
            processList[0].Pages.Add(pages[^1]);
        }
    }
}