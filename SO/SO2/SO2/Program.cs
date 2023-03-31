using SO2;
using SO2.Algorithms;

public class Program {
    private static void Main() {
        const int cylinderCount = 200;

        List<Request> requestList = RequestGenerator.Generate(30, cylinderCount, 100);

        Algorithm[] algorithms = {
            new FCFSAlgorithm(RequestGenerator.CloneRequests(requestList), cylinderCount)
        };
        
        
    }
}