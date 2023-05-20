namespace SO4; 

public class AlgorithmDataBuilder {
    private int pageCount = 50;
    private int processCount = 10;
    private int processRequestCount = 20;
    private int processRequestCountDeviation = 25;
    private int localChancePercentage = 5;
    private int localSeriesLength = 3;
    private int localSeriesLengthDeviation = 2;

    public AlgorithmData Generate() {
        var pageList = new List<Page>();
        for (int i = 0; i < pageCount; i++) {
            pageList.Add(new Page());
        }

        var processList = new List<Process>();
        var random = new Random();

        for (int i = 0; i < processCount; i++) {
            int requestCount = processRequestCount + random.Next(-processRequestCountDeviation, processRequestCountDeviation + 1);
            if (requestCount < 1) {
                requestCount = 1;
            }

            var requestList = new List<int>();

            for (int j = 0; j < requestCount; j++) {
                int localChance = random.Next(1, 101);
                if (localChance <= localChancePercentage) {
                    int seriesCount = localSeriesLength + random.Next(-localSeriesLengthDeviation, localSeriesLengthDeviation + 1);
                    seriesCount = Math.Clamp(seriesCount, 1, requestCount - j);

                    int seriesRequest = random.Next(1, pageCount + 1);
                    for (int d = 0; d < seriesCount; d++) {
                        int deviation = random.Next(-localSeriesLengthDeviation, localSeriesLengthDeviation + 1);
                        int calcRequest = Math.Clamp(seriesRequest + deviation, 1, pageCount);
                        requestList.Add(calcRequest);
                    }
                }
                else {
                    requestList.Add(random.Next(1, pageCount + 1));
                }
            }
            processList.Add(new Process(requestList));
        }

        return new AlgorithmData(pageList, processList);
    }
    
    public AlgorithmDataBuilder SetPageCount(int pageCount) {
        if (this.pageCount <= 0) {
            throw new ArgumentException();
        }
        this.pageCount = pageCount;
        return this;
    }

    public AlgorithmDataBuilder SetProcessCount(int processCount) {
        if (this.processCount <= 0) {
            throw new ArgumentException();
        }
        this.processCount = processCount;
        return this;
    }

    public AlgorithmDataBuilder SetProcessRequestCount(int processRequestCount) {
        if (processRequestCount <= 0) {
            throw new ArgumentException();
        }
        this.processRequestCount = processRequestCount;
        return this;
    }
    
    public AlgorithmDataBuilder SetProcessRequestCountDeviation(int processRequestCountDeviation) {
        if (processRequestCount < 0) {
            processRequestCountDeviation = 0;
        }
        this.processRequestCountDeviation = processRequestCountDeviation;
        return this;
    }
    
    public AlgorithmDataBuilder SetLocalChangePercentage(int localChancePercentage) {
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