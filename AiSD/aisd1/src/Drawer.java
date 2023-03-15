public class Drawer {
    private static String drawLine(int n, char ch) {
        String line = "";
        
        for(int i = 0; i < n; i++) {
            line += ch;
        }
        
        return line;
    }
    
    public static String drawOffsetPyramid(int n, int margin) {
        if(n < 1 || margin < 0) {
            throw new IllegalArgumentException();
        }
        
        int pyramidWidth = (n - 1) * 2 + margin * 2;
        
        StringBuilder pyramid = new StringBuilder();
        
        for(int i = 0; i < n; i++) {
            String line = "";

            line += drawLine(n - i - 1 + margin, '.');
            line += drawLine(i * 2 + 1, 'X');
            line += drawLine(n - i - 1 + margin, '.');
            pyramid.append(line).append("\n");
        }
        return pyramid.toString();
    }
    
    public static void drawPyramid(int n) {
        System.out.print(drawOffsetPyramid(n, 0));
    }

    public static void drawChristmassTree(int n) {
        for(int i = 1; i <= n; i++) {
            System.out.print(drawOffsetPyramid(i, n - i));
        }
    }
    
    public static void drawSquare(int size) {
        System.out.println(drawLine(size, 'X'));
        
        for(int i = 0; i < size - 2; i++) {
            System.out.print(drawLine(1, 'X'));
            System.out.print(drawLine(size - 2, '.'));
            System.out.print(drawLine(1, 'X'));
            System.out.println();
        }
        System.out.println(drawLine(size, 'X'));
    }
}