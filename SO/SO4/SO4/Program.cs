using SO4;

AlgorithmData data = new AlgorithmDataBuilder()
    .Generate();

foreach (var request in data.Processes.SelectMany(r => r.RequestList)) {
    Console.Write(request + ", ");
}    