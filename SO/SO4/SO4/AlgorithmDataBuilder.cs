namespace SO4; 

public class AlgorithmDataBuilder {
    private int pageCount = 50;
    private int maxRequest = 20;
    private int processCount = 10;
    private int minProcessRequestCount = 20;
    private int maxProcessRequestCount = 50;
    private int localChancePercentage = 5;
    private int localSeriesLength = 3;
    private int localSeriesLengthDeviation = 2;

    public AlgorithmData Generate() {
        var pages = new List<Page>();
        for (int i = 0; i < pageCount; i++) {
            pages.Add(new Page());
        }

        var processes = new List<Process>();
        var random = new Random();

        for (int i = 0; i < processCount; i++) {
            int requestCount = random.Next(minProcessRequestCount, maxProcessRequestCount + 1);

            var requestList = new List<int>();

            for (int j = 0; j < requestCount; j++) {
                int localChance = random.Next(1, 101);
                if (localChance <= localChancePercentage) {
                    int seriesCount = localSeriesLength + random.Next(-localSeriesLengthDeviation, localSeriesLengthDeviation + 1);
                    seriesCount = Math.Clamp(seriesCount, 1, requestCount - j);

                    int seriesRequest = random.Next(1, maxRequest + 1);
                    for (int d = 0; d < seriesCount; d++) {
                        int deviation = random.Next(-localSeriesLengthDeviation, localSeriesLengthDeviation + 1);
                        int calcRequest = Math.Clamp(seriesRequest + deviation, 1, maxRequest);
                        requestList.Add(calcRequest);
                    }
                }
                else {
                    requestList.Add(random.Next(1, maxRequest));
                }
            }
            processes.Add(new Process(new Queue<int>(requestList)));
        }

        return new AlgorithmData(pages, processes);
    }
    
    public AlgorithmDataBuilder SetPageCount(int pageCount) {
        if (this.pageCount <= 0) {
            throw new ArgumentException();
        }
        this.pageCount = pageCount;
        return this;
    }
    
    public AlgorithmDataBuilder SetMaxRequest(int maxRequest) {
        if (this.maxRequest < 1) {
            maxRequest = 1;
        }
        this.maxRequest = maxRequest;
        return this;
    }

    public AlgorithmDataBuilder SetProcessCount(int processCount) {
        if (this.processCount <= 0) {
            throw new ArgumentException();
        }
        this.processCount = processCount;
        return this;
    }

    public AlgorithmDataBuilder SetMaxProcessRequestCount(int maxProcessRequestCount) {
        if (maxProcessRequestCount < 1) {
            maxProcessRequestCount = 1;
        }
        this.maxProcessRequestCount = maxProcessRequestCount;
        return this;
    }
    
    public AlgorithmDataBuilder SetMinProcessRequestCount(int minProcessRequestCount) {
        if (minProcessRequestCount < 1) {
            minProcessRequestCount = 1;
        }
        this.minProcessRequestCount = minProcessRequestCount;
        return this;
    }
    
    public AlgorithmDataBuilder SetLocalChancePercentage(int localChancePercentage) {
        if (localChancePercentage < 0) {
            throw new ArgumentException();
        }
        this.localChancePercentage = localChancePercentage;
        return this;
    }
    
    public AlgorithmDataBuilder SetLocalSeriesLength(int localSeriesLength) {
        if (localSeriesLength < 1) {
            localSeriesLength = 1;
        }
        this.localSeriesLength = localSeriesLength;
        return this;
    }
    
    public AlgorithmDataBuilder SetLocalSeriesLengthDeviation(int localSeriesLengthDeviation) {
        if (localSeriesLengthDeviation < 0) {
            localSeriesLengthDeviation = 0;
        }
        this.localSeriesLengthDeviation = localSeriesLengthDeviation;
        return this;
    }
}