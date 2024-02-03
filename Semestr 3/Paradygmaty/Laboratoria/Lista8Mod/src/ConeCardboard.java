import Utils.Cuboid;

public class ConeCardboard extends Cardboard
{
    private double _radius;
    private double _height;
    
    public ConeCardboard(double radius, double height)
    {
        _radius = radius;
        _height = height;
    }
    
    @Override
    public double getVolume()
    {
        return Math.PI * Math.pow(_radius, 2) * (_height / 3);
    }

    @Override
    public Cuboid getBiggestFittingInsideCuboid()
    {
        var cuboidWidth = 2 * Math.sqrt(2) / 3 * _radius;
        var cuboidHeight = _height / 3;
        return new Cuboid(cuboidWidth, cuboidWidth, cuboidHeight);
    }

    @Override
    public Cuboid getSmallestFittingOutsideCuboid()
    {
        return new Cuboid(_radius * 2, _radius * 2, _height);
    }

    @Override
    public String getCardboardType()
    {
        return "Cone";
    }
}
