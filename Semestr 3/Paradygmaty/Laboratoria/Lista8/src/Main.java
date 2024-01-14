import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        var cardboards = new ArrayList<Cardboard>()
        {
            {
                add(new BallCardboard(3));
                add(new TubeCardboard(2, 4));
                add(new BallCardboard(5));
                add(new TubeCardboard(3, 6));
                add(new RectCardboard(2, 3, 4));
                add(new BallCardboard(2));
                add(new RectCardboard(1, 2, 3));
                add(new RectCardboard(6, 6, 3));
                add(new RectCardboard(2, 2, 2));
                add(new BallCardboard(7));
                add(new TubeCardboard(4, 8));
            }
        };
        
        var elf = new Elf(cardboards);
        elf.sortCardboards();
        
        System.out.println("Sorted cardboards volume: " + elf.getSortedCardboardsVolume());
        System.out.println(elf.displaySortedCardboards());
    }
}