package NoPolymorphism;

import Utils.Cuboid;

public class Cardboard
{
    private final CardboardType _cardboardType;
    private final double[] _sizes;
    
    public Cardboard(double[] sizes, CardboardType cardboardType)
    {
        _cardboardType = cardboardType;
        _sizes = sizes;
    }
    
    public double getVolume()
    {
        switch(_cardboardType)
        {
            case Rect ->
            {
                return _sizes[0] * _sizes[1] * _sizes[2];
            }
            case Ball ->
            {
                return (double) 4 / 3 * Math.PI * Math.pow(_sizes[0], 3);
            }
            case Tube ->
            {
                return Math.PI * Math.pow(_sizes[0], 2) * _sizes[1];
            }
            case Cone ->
            {
                return Math.PI * Math.pow(_sizes[0], 2) * (_sizes[1] / 3);
            }
        }
        return 0;
    }
    
    public Cuboid getBiggestFittingInsideCuboid()
    {
        switch(_cardboardType)
        {
            case Rect ->
            {
                return new Cuboid(_sizes[1], _sizes[2], _sizes[0]);
            }
            case Ball ->
            {
                var cuboidSize = _sizes[0] * 2 / Math.sqrt(3);
                return new Cuboid(cuboidSize, cuboidSize, cuboidSize);
            }
            case Tube ->
            {
                var cuboidWidth = (2 * _sizes[0]) / Math.sqrt(2);
                return new Cuboid(cuboidWidth, _sizes[1], cuboidWidth);
            }
            case Cone ->
            {
                var cuboidWidth = 2 * Math.sqrt(2) / 3 * _sizes[0];
                var cuboidHeight = _sizes[1] / 3;
                return new Cuboid(cuboidWidth, cuboidWidth, cuboidHeight);
            }
        }
        return null;
    }
    
    public Cuboid getSmallestFittingOutsideCuboid()
    {
        switch(_cardboardType)
        {
            case Rect ->
            {
                return new Cuboid(_sizes[0], _sizes[1], _sizes[2]);
            }
            case Ball ->
            {
                var diameter = _sizes[0] * 2;
                return new Cuboid(diameter, diameter, diameter);
            }
            case Tube ->
            {
                return new Cuboid(_sizes[0] * 2, _sizes[0] * 2, _sizes[1]);
            }
            case Cone ->
            {
                return new Cuboid(_sizes[0] * 2, _sizes[0] * 2, _sizes[1]);
            }
        }
        return null;
    }
    
    @Override
    public String toString()
    {
        return String.format("Name: %s, Volume: %f", _cardboardType, getVolume());
    }
}
