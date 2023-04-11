public class Rectangle extends Shape {
    private int width;
    private int height;

    public Rectangle(String name, int width, int height) {
        super(name);
        this.width = width;
        this.height = height;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    @Override
    public float getArea() {
        return width * height;
    }

    @Override
    public float getDelimeter() {
        return 2 * width + 2 * height;
    }
}
