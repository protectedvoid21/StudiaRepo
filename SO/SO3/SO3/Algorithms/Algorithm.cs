namespace SO3.Algorithms; 

public abstract class Algorithm {
    public string Name { get; }
    public int FailureCount { get; protected set; }
    protected readonly Page[] pages;
    private readonly int[] requests;
    protected int tick;

    protected Algorithm(Page[] pages, int[] requests, string name) {
        this.pages = pages;
        this.requests = requests;
        Name = name;
    }

    protected abstract Page GetAvailablePage(int request);

    public void Execute() {
        foreach (var request in requests) {
            tick++;
            Page availablePage = GetAvailablePage(request);

            availablePage.SetReference(request, tick);
        }
    }
}