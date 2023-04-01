namespace SO2; 

public static class RequestGenerator {
    public static List<Request> Generate(int processCount, int cylinderCount, int maxArrivalTime) {
        List<Request> requests = new();

        Random random = new();
        for (int i = 0; i < processCount; i++) {
            requests.Add(new Request(random.Next(cylinderCount) + 1, random.Next(maxArrivalTime)));
        }

        return requests.OrderBy(r => r.ArrivalTime).ToList();
    }

    public static List<Request> GenerateCustom(IEnumerable<int> cylinderIndexes, int cylinderCount) {
        return cylinderIndexes.Select(index => new Request(index, 0)).ToList();
    }

    public static List<Request> CloneRequests(IEnumerable<Request> requestList) {
        return requestList.Select(r => new Request(r.Cylinder, r.ArrivalTime)).ToList();
    }
}