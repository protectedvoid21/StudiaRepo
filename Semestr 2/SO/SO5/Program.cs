using SO5;
using SO5.Algorithms;

const int processorCount = 10;
const int minRequestSize = 3;
const int maxRequestSize = 40;
const int minRequestCount = 15;
const int maxRequestCount = 60;
const int threshold = 70;
const int maxAskCount = 5;

var data = new DataGenerator()
    .SetProcessorCount(processorCount)
    .SetMaxAppearTime(100)
    .SetMinRequestSize(minRequestSize)
    .SetMaxRequestSize(maxRequestSize)
    .SetMinRequestCount(minRequestCount)
    .SetMaxRequestCount(maxRequestCount)
    .Generate();

var algorithms = new Algorithm[] {
    new StrategyFirst(data.GetCopy(), "First", threshold, maxAskCount: 5),
    new StrategySecond(data.GetCopy(), "Second", threshold),
    new StrategyThird(data.GetCopy(), "Third", threshold, minThreshold: 25, transferPercentage: 25),
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
AlgorithmAnalizer.Create(algorithmStatsList, processorCount, minRequestSize, maxRequestSize, minRequestCount,
    maxRequestCount, threshold, maxAskCount);