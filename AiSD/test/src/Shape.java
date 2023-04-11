public abstract class Shape {
    private String name;
    
    public Shape(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void display() {
        System.out.println(name);
        System.out.println("Area : " + getArea());
        System.out.println("Delimeter : " + getDelimeter());
    }
    
    public abstract float getArea();
    public abstract float getDelimeter();
}
