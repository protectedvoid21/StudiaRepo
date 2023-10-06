namespace SO4; 

public class Page {
    public int Request { get; private set; }
    public int SwitchedTick { get; private set; }
    public int LastUsed { get; private set; }
    public bool IsEmpty => Request == 0;

    public void SetReference(int request, int tick) {
        if (request != Request) {
            SwitchedTick = tick;
        }

        LastUsed = tick;
        Request = request;
    }
}