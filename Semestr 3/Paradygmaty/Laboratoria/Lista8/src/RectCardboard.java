import Utils.Cuboid;

public class RectCardboard extends Cardboard
{
    private double _length;
    private double _width;
    private double _height;

    public RectCardboard(double length, double width, double height)
    {
        _length = length;
        _width = width;
        _height = height;
    }

    public double getVolume()
    {
        return _length * _width * _height;
    }

    @Override
    public Cuboid getBiggestFittingInsideCuboid()
    {
        return new Cuboid(_width, _height, _length);
    }

    @Override
    public Cuboid getSmallestFittingOutsideCuboid()
    {
        return new Cuboid(_width, _height, _length);
    }

    @Override
    public String getCardboardType()
    {
        return "Rect";
    }
}
