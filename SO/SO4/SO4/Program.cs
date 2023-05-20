using SO4;
using SO4.Algorithms;

const int pageCount = 35;
const int processCount = 10;
const int maxRequest = 20;

AlgorithmData data = new AlgorithmDataBuilder()
    .SetPageCount(pageCount)
    .SetProcessCount(processCount)
    .SetProcessRequestCount(40)
    .SetProcessRequestCountDeviation(15)
    .SetMaxRequest(maxRequest)
    .Generate();

var algorithms = new Algorithm[] {
    new EqualAlgorithm(data, "Equal")
};

var algorithmStatsList = new List<AlgorithmStats>();
foreach (var algorithm in algorithms) {
    algorithm.Execute();
    algorithmStatsList.Add(new AlgorithmStats(algorithm));
}

var algorithmInitData = new AlgorithmInitData(algorithmStatsList, processCount, pageCount, maxRequest);
AlgorithmAnalizer.Create(algorithmInitData);
