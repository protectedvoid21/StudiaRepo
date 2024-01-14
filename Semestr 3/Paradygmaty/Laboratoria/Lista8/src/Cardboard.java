import Utils.Cuboid;

public abstract class Cardboard
{
    public abstract double getVolume();
    
    public abstract Cuboid getBiggestFittingInsideCuboid();
    
    public abstract Cuboid getSmallestFittingOutsideCuboid();
    
    public abstract String getCardboardType();
    
    @Override
    public String toString()
    {
        return String.format("Name: %s, Volume: %f", getCardboardType(), getVolume());
    }
}

