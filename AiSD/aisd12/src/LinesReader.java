import java.util.Scanner;

public class LinesReader {
    String concatLines(int howMany, Scanner scanner) {
        var stringBuffer = new StringBuffer();
        
        for (int i = 0; i < howMany; i++) {
            stringBuffer.append(scanner.nextLine());
        }
        
        return stringBuffer.toString();
    }

}
