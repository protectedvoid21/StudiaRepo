import Utils.Cuboid;

public class BallCardboard extends Cardboard
{
    private double _radius;
    
    public BallCardboard(double radius)
    {
        _radius = radius;
    }

    public double getVolume()
    {
        return 4.0d / 3.0d * 3.1415d * Math.pow(_radius, 3);
    }

    @Override
    public Cuboid getBiggestFittingInsideCuboid()
    {
        var cuboidSize = _radius * 2 / Math.sqrt(3);
        return new Cuboid(cuboidSize, cuboidSize, cuboidSize);
    }

    @Override
    public Cuboid getSmallestFittingOutsideCuboid()
    {
        var diameter = _radius * 2;
        return new Cuboid(diameter, diameter, diameter);
    }

    @Override
    public String getCardboardType()
    {
        return "Ball";
    }
}