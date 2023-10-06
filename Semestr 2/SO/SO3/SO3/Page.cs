namespace SO3; 

public class Page {
    public int Request { get; private set; }
    public int SwitchedTick { get; private set; }
    public int LastUsed { get; private set; }
    public bool IsEmpty => Request == 0;

    public bool HasSecondChance { get; private set; }
    
    public void SetReference(int request, int tick) {
        if (request != Request) {
            SwitchedTick = tick;
        }

        LastUsed = tick;
        Request = request;
        HasSecondChance = true;
    }

    public void RemoveSecondChance() {
        HasSecondChance = false;
    }
}