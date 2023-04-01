using SO2;
using SO2.Algorithms;

public class Program {
    private static void Main() {
        const int cylinderCount = 200;

        //List<Request> requestList = RequestGenerator.Generate(10000, cylinderCount, 1000);
        //List<Request> requestList = RequestGenerator.GenerateCustom(new[] { 98, 183, 37, 122, 14, 124, 65, 67 }, 200);
        List<Request> requestList = RequestGenerator.GenerateCustom(new[] { 53, 65, 98, 183, 37, 122, 14, 124, 67 }, 200);

        Algorithm[] algorithms = {
            new FCFSAlgorithm(RequestGenerator.CloneRequests(requestList), "FCFS"),
            new SSTFAlgorithm(RequestGenerator.CloneRequests(requestList), "SSTF"),
            new SCANAlgorithm(RequestGenerator.CloneRequests(requestList), "SCAN", cylinderCount),
            new CSCANAlgorithm(RequestGenerator.CloneRequests(requestList), "C-SCAN", cylinderCount),
        };

        List<AlgorithmStats> algorithmStatsList = new();
        
        Console.WriteLine("DISK ACCESS ALGORITHMS SIMULATION");
        foreach (var algorithm in algorithms) {
            Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
            algorithm.Execute();
            algorithmStatsList.Add(new AlgorithmStats(algorithm));
            Console.WriteLine($"[COMPLETED] {algorithm.Name}");
        }
        
        Console.Clear();
        AlgorithmAnalizer.Create(algorithmStatsList);
    }
}