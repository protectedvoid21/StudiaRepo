namespace SO1;

public class Process {
    public int Amount { get; private set; }
    public int InitialAmount { get; init; }
    public int ArrivalTime { get; init; }
    public int WaitingTime { get; private set; }
    public bool IsCompleted => Amount == 0;

    public Process(int amount, int arrivalTime) {
        Amount = amount;
        ArrivalTime = arrivalTime;
        InitialAmount = amount;
    }

    public int ExecutePartly(int units) {
        int burntAmount = Amount - units >= 0 ? units : Amount;
        Amount -= units;
        if(Amount < 0) {
            Amount = 0;
        }

        return burntAmount;
    }

    public void Execute() {
        Amount = 0;
    }

    public void AddWaitingTime(int time) {
        WaitingTime += time;
    }
}