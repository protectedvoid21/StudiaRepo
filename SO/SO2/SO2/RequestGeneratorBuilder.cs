namespace SO2; 

public class RequestGeneratorBuilder {
    private int requestCount;
    private int cylinderCount;
    private int maxArrivalTime;
    private int deadlinePercentage;
    private int minDeadline;
    private int maxDeadline;

    public List<Request> Generate() {
        List<Request> requests = new();
        
        Random random = new();
        for (int i = 0; i < requestCount; i++) {
            int deadline = 0;
            
            if (random.Next(100) + 1 < deadlinePercentage) {
                deadline = random.Next(minDeadline, maxDeadline + 1);
            }
            requests.Add(new Request(random.Next(cylinderCount) + 1, random.Next(maxArrivalTime), deadline));
        }
        
        return requests.OrderBy(r => r.ArrivalTime).ToList();
    }

    public RequestGeneratorBuilder SetRequests(int requestCount) {
        if (requestCount <= 0) {
            throw new ArgumentException();
        }

        this.requestCount = requestCount;
        return this;
    }

    public RequestGeneratorBuilder SetCylinderCount(int cylinderCount) {
        if (cylinderCount <= 0) {
            throw new ArgumentException();
        }

        this.cylinderCount = cylinderCount;
        return this;
    }

    public RequestGeneratorBuilder SetMaxArrivalTime(int maxArrivalTime) {
        if (maxArrivalTime < 0) {
            maxArrivalTime = 0;
        }
        
        this.maxArrivalTime = maxArrivalTime;
        return this;
    }
    
    public RequestGeneratorBuilder SetDeadlinePercentage(int deadlinePercentage) {
        if (deadlinePercentage < 0 || deadlinePercentage > 100) {
            throw new ArgumentException();
        }

        this.deadlinePercentage = deadlinePercentage;
        return this;
    }
    
    public RequestGeneratorBuilder SetMinimumDeadline(int minDeadline) {
        if (minDeadline < 0) {
            minDeadline = 0;
        }

        this.minDeadline = minDeadline;
        return this;
    }
    
    public RequestGeneratorBuilder SetMaximumDeadline(int maxDeadline) {
        if (maxDeadline < 0) {
            maxDeadline = 0;
        }

        this.maxDeadline = maxDeadline;
        return this;
    }
}