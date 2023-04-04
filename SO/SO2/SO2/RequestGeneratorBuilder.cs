namespace SO2; 

public class RequestGeneratorBuilder {
    private int requestCount;
    private int cylinderCount;
    private int maxArrivalTime;

    private int minCylinder;
    private int maxCylinder;
    
    private int deadlinePercentage;
    private int minDeadline;
    private int maxDeadline;

    public RequestGeneratorBuilder() {
        requestCount = 100;
        cylinderCount = 200;
        maxArrivalTime = 100;
        deadlinePercentage = 10;
        minDeadline = 10;
        maxDeadline = 100;
        minCylinder = 1;
        maxCylinder = cylinderCount;
    }

    public List<Request> Generate() {
        List<Request> requests = new();
        
        Random random = new();
        int deadlineCount = requestCount - (int)(requestCount * (float)(100 - deadlinePercentage) / 100);
        
        for (int i = 0; i < requestCount - deadlineCount; i++) {
            requests.Add(new Request(random.Next(minCylinder, maxCylinder + 1), random.Next(maxArrivalTime)));
        }

        for (int i = 0; i < deadlineCount; i++) {
            int deadline = random.Next(minDeadline, maxDeadline + 1);
            
            requests.Add(new Request(random.Next(minCylinder, maxCylinder + 1), random.Next(maxArrivalTime), deadline));
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
    
    public RequestGeneratorBuilder SetMinCylinder(int minCylinder) {
        if (minCylinder > cylinderCount) {
            minCylinder = cylinderCount;
        }
        if (minCylinder < 1) {
            minCylinder = 1;
        }

        this.minCylinder = minCylinder;
        return this;
    }
    
    public RequestGeneratorBuilder SetMaxCylinder(int maxCylinder) {
        if (maxCylinder < minCylinder) {
            maxCylinder = minCylinder;
        }

        if (maxCylinder > cylinderCount) {
            maxCylinder = cylinderCount;
        }
        if (maxCylinder < 1) {
            maxCylinder = 1;
        }

        this.maxCylinder = maxCylinder;
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