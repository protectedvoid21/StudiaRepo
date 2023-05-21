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
    new ProportionalAlgorithm(data.GetCopy(), "Proportional")
};

var algorithmStatsList = new List<AlgorithmStats>();
foreach (var algorithm in algorithms) {
    algorithm.Execute();
    algorithmStatsList.Add(new AlgorithmStats(algorithm));
}

var algorithmInitData = new AlgorithmInitData(algorithmStatsList, processCount, pageCount, maxRequest);
AlgorithmAnalizer.Create(algorithmInitData);
