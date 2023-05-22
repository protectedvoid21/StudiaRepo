using SO4;
using SO4.Algorithms;

const int pageCount = 50;
const int processCount = 15;
const int maxRequest = 30;

AlgorithmData data = new AlgorithmDataBuilder()
    .SetPageCount(pageCount)
    .SetProcessCount(processCount)
    .SetProcessRequestCount(70)
    .SetProcessRequestCountDeviation(40)
    .SetMaxRequest(maxRequest)
    .SetLocalChancePercentage(20)
    .SetLocalSeriesLength(5)
    .Generate();

var algorithms = new Algorithm[] {
    new EqualAlgorithm(data.GetCopy(), "Equal"),
    new ProportionalAlgorithm(data.GetCopy(), "Proportional"),
    new FrequencyControlAlgorithm(data.GetCopy(), "FreqControl", 0.4f, 0.7f, 5),
};

Console.WriteLine("Memory access algorithms \n ---------------------------------------------------------------");
var algorithmStatsList = new List<AlgorithmStats>();
foreach (var algorithm in algorithms) {
    Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
    algorithm.Execute();
    Console.WriteLine($"[COMPLETED] {algorithm.Name}.");
    algorithmStatsList.Add(new AlgorithmStats(algorithm));
}

Console.Clear();
var algorithmInitData = new AlgorithmInitData(algorithmStatsList, processCount, pageCount, maxRequest);
AlgorithmAnalizer.Create(algorithmInitData);
