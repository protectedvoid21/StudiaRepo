namespace SO5;

public record AlgorithmData(Processor[] Processors, List<Request> Requests) {
    public AlgorithmData GetCopy() {
        var processesCopy = Processors.Select(_ => new Processor()).ToArray();
        var requestsCopy = Requests.Select(r => new Request(r.ProcessorId, r.Amount, r.AppearTime)).ToList();

        return new AlgorithmData(processesCopy, requestsCopy);
    }
}