using SO3;
using SO3.Algorithms;

const int pageCount = 1000;
const int requestCount = 3500;
const int maxRequest = 5000;

var pages = Generator.GetPages(pageCount);
var requests = Generator.GetRequests(requestCount, maxRequest);

Algorithm[] algorithms = {
    new FIFOAlgorithm(Generator.CopyPages(pages), requests, "FIFO"),
    new OPTAlgorithm(Generator.CopyPages(pages), requests, "OPT"),
    new LRUAlgorithm(Generator.CopyPages(pages), requests, "LRU"),
    new ALRUAlgorithm(Generator.CopyPages(pages), requests, "ApxLRU"),
    new RANDAlgorithm(Generator.CopyPages(pages), requests, "RAND"),
};
List<AlgorithmStats> algorithmStatsList = new();

Console.WriteLine("DISK ACCESS ALGORITHMS SIMULATION");
foreach (var algorithm in algorithms) {
    Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
    algorithm.Execute();
    algorithmStatsList.Add(new AlgorithmStats(algorithm));
    Console.WriteLine($"[COMPLETED] {algorithm.Name}");
}

//Console.Clear();
AlgorithmAnalizer.Create(algorithmStatsList, pageCount, requestCount, maxRequest);