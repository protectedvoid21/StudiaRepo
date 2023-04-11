import java.util.ArrayList;
import java.util.HashMap;

public class Main {
    public static void main(String[] args) {
        Rectangle rect = new Rectangle("Muj prostokont" , 7, 9);
        Shape circ = new Circle("Kulko", 5);
        
        Displayer.introduce(rect.getName());
        Displayer.drawData("Dlugosc", rect.getWidth());
        Displayer.drawData("Wysokosc", rect.getHeight());
        Displayer.drawData("Powierzchnia", rect.getArea());
        Displayer.drawLine();
    }
}