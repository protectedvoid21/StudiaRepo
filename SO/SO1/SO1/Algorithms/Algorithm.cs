namespace SO1.Algorithms;

public abstract class Algorithm {
    public string Name { get; init; }
    protected List<Process> processList;
    public List<Process> ExecutedProcesses { get; protected set; }

    protected Algorithm(List<Process> processList, string name) {
        this.processList = processList;
        ExecutedProcesses = new();
        Name = name;
    }

    public abstract void Execute();
}