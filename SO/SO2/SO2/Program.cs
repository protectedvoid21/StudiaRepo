using SO2;
using SO2.Algorithms;

public class Program {
    private static void Main() {
        const int cylinderCount = 200;

        List<Request> requestList = RequestGenerator.Generate(100, cylinderCount, 1000);

        Algorithm[] algorithms = {
            new FCFSAlgorithm(RequestGenerator.CloneRequests(requestList), "FCFS", cylinderCount),
            new SSTFAlgorithm(RequestGenerator.CloneRequests(requestList), "SSTF", cylinderCount)
        };

        List<AlgorithmStats> algorithmStatsList = new();
        foreach (var algorithm in algorithms) {
            algorithm.Execute();
            algorithmStatsList.Add(new AlgorithmStats(algorithm));
        }
        
        AlgorithmAnalizer.Create(algorithmStatsList);
    }
}