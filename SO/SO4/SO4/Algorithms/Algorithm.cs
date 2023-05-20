namespace SO4.Algorithms; 

public abstract class Algorithm {
    public string Name { get; }
    public readonly List<Process> CompletedProcesses = new();
    
    protected readonly List<Process> processList;
    protected readonly Page[] pages;
    protected int tick;
    protected readonly int tickCount;

    protected Algorithm(AlgorithmData data, string name) {
        pages = data.Pages;
        processList = data.ProcessList;
        Name = name;

        tickCount = processList.Max(p => p.RequestQueue.Count);
    }

    protected abstract void SetProcessesPages();

    public virtual void Execute() {
        SetProcessesPages();
    }
}