import java.util.ArrayList;
import java.util.HashMap;

public class Displayer {
    /*public static void info(String name, HashMap<String, Double> dict){
        String displayText = "" +
                "|-------------------------\n" +
                "|-- " + name + ":                   \n" +
                "|-------------------------\n";
        
        for(var pair : dict.entrySet()) {
            displayText += "|-- " + pair.getKey() + ": " + pair.getValue() +":               \n";
        }
        
        displayText += "|-------------------------\n";
        
        System.out.println(displayText);
    }*/

    public static void introduce(String name) {
        drawLine();
        System.out.println("|-- " + name);
        drawLine();
    }
    
    public static void drawData(String name, double value) {
        System.out.printf("|-- %s \t : \t %.2f\n", name, value);
    }
    
    public static void drawLine() {
        System.out.println("|----------------------------------");
    }
}
