import Utils.Cuboid;

public class TubeCardboard extends Cardboard
{
    private final double _radius;
    private final double _height;

    public TubeCardboard(double radius, double height)
    {
        _radius = radius;
        _height = height;
    }

    public double getVolume()
    {
        return Math.PI * Math.pow(_radius, 2) * _height;
    }

    @Override
    public Cuboid getBiggestFittingInsideCuboid()
    {
        var cuboidWidth = (2 * _radius) / Math.sqrt(2);
        return new Cuboid(cuboidWidth, _height, cuboidWidth);
    }

    @Override
    public Cuboid getSmallestFittingOutsideCuboid()
    {
        return new Cuboid(_radius * 2, _radius * 2, _height);
    }

    @Override
    public String getCardboardType()
    {
        return "Tube";
    }
}
