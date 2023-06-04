namespace SO5;

public class DataGenerator {
    private int _processorCount = 10;
    private int _maxAppearTime = 100;
    private int _minRequestSize = 1;
    private int _maxRequestSize = 10;
    private int _minRequestCount = 10;
    private int _maxRequestCount = 30;

    public AlgorithmData Generate() {
        var processes = new Processor[_processorCount];
        var requests = new List<Request>();

        for (int i = 0; i < _processorCount; i++) {
            processes[i] = new Processor();
        }

        var random = new Random();

        for (int i = 0; i < _processorCount; i++) {
            int requestCount = random.Next(_minRequestCount, _maxRequestCount);
            for (int j = 0; j < requestCount; j++) {
                int processId = random.Next(0, _processorCount);
                int amount = random.Next(_minRequestSize, _maxRequestSize + 1);
                int appearTime = random.Next(1, _maxAppearTime + 1);
                
                requests.Add(new Request(processId, amount, appearTime));
            }
        }
        requests = requests.OrderBy(r => r.AppearTime).ToList();

        return new AlgorithmData(processes, requests);
    }

    public DataGenerator SetProcessorCount(int processorCount) {
        if (processorCount < 1) {
            processorCount = 1;
        }

        _processorCount = processorCount;
        return this;
    }

    public DataGenerator SetMaxAppearTime(int maxAppearTime) {
        if (maxAppearTime < 1) {
            maxAppearTime = 1;
        }

        _maxAppearTime = maxAppearTime;
        return this;
    }

    public DataGenerator SetMinRequestSize(int minRequestSize) {
        if (minRequestSize < 1) {
            minRequestSize = 1;
        }

        if (minRequestSize > _maxRequestSize) {
            minRequestSize = _maxRequestSize;
        }

        _minRequestSize = minRequestSize;
        return this;
    }
    
    public DataGenerator SetMaxRequestSize(int maxRequestSize) {
        if (maxRequestSize < 1) {
            maxRequestSize = 1;
        }
        _maxRequestSize = maxRequestSize;
        return this;
    }
    
    public DataGenerator SetMinRequestCount(int minRequestCount) {
        if (minRequestCount < 1) {
            minRequestCount = 1;
        }

        if (minRequestCount > _maxRequestCount) {
            minRequestCount = _maxRequestCount;
        }

        _minRequestCount = minRequestCount;
        return this;
    }
    
    public DataGenerator SetMaxRequestCount(int maxRequestCount) {
        if (maxRequestCount < 1) {
            maxRequestCount = 1;
        }
        if (maxRequestCount < _minRequestCount) {
            maxRequestCount = _minRequestCount;
        }
        _maxRequestCount = maxRequestCount;
        return this;
    }
}