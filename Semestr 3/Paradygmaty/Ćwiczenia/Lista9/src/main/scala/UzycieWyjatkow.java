public class UzycieWyjatkow {
    public static void main(String[] args) {
        try {
            metoda1();
        } catch ( Exception e ) {
            System.err.println( e.getMessage() + "\n" );
            e.printStackTrace();
        }
    }
    public static void metoda1() throws Exception {
        metoda2();
    }
    public static void metoda2() throws Exception {
        metoda3();
    }
    public static void metoda3() throws Exception {
        throw new Exception( "Wyjatek zgloszony w metoda3" );
    }
}