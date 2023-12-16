class RefCounter
{
private:
    int count;
    
public:
    RefCounter()
    {
        count = 1;
    }

    int add()
    {
        return ++count;
    }

    int dec()
    {
        return --count;
    };

    int get()
    {
        return count;
    }
};