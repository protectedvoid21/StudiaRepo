package Utils;

public record Cuboid(double width, double height, double length) 
{
    public double getVolume()
    {
        return width * height * length;
    }
}