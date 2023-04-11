public class Circle extends Shape {
    private int radius;
    
    public Circle(String name, int radius) {
        super(name);
        this.radius = radius;
    }
    
    @Override
    public float getArea() {
        return (float)Math.PI * radius * radius;
    }

    @Override
    public float getDelimeter() {
        return 2 * (float)Math.PI * radius;
    }
}
