namespace SO4; 

public class AlgorithmDataBuilder {
    private int pageCount = 50;
    private int processCount = 10;
    private int processRequestCount = 40;
    private int processRequestCountDeviation = 5;
    private int localChancePercentage = 5;
    private int localSeriesLength = 3;
    private int localSeriesLengthDeviation = 2;

    public AlgorithmData Generate() {
        
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