namespace SO1.Algorithms;

public abstract class Algorithm {
    protected List<Process> processList;
    public List<Process> ExecutedProcesses { get; protected set; }
    public string Name { get; init; }
    public int ChangeCount { get; protected set; }

    protected Algorithm(List<Process> processList, string name) {
        this.processList = processList;
        ExecutedProcesses = new();
        Name = name;
    }

    public abstract void Execute();
}