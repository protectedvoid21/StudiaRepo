using SO5;
using SO5.Algorithms;

const int threshold = 70;
const int maxAskCount = 10;

var data = new DataGenerator()
    .SetProcessorCount(10)
    .SetMaxAppearTime(100)
    .SetMinRequestSize(3)
    .SetMaxRequestSize(40)
    .SetMinRequestCount(5)
    .SetMaxRequestCount(30)
    .Generate();

var algorithms = new Algorithm[] {
    new StrategyFirst(data.GetCopy(), "First", threshold, 10),
    new StrategySecond(data.GetCopy(), "Second", threshold),
    new StrategyThird(data.GetCopy(), "Third", threshold, 25, 25),
};

Console.WriteLine("Process usage strategies \n ---------------------------------------------------------------");
var algorithmStatsList = new List<AlgorithmStats>();
foreach (var algorithm in algorithms) {
    Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
    algorithm.Execute();
    Console.WriteLine($"[COMPLETED] {algorithm.Name}.");
    algorithmStatsList.Add(new AlgorithmStats(algorithm));
}

Console.Clear();
AlgorithmAnalizer.Create(algorithmStatsList);

