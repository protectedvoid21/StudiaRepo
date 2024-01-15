package NoPolymorphism;

import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        var cardboards = new ArrayList<Cardboard>()
        {
            {
                add(new Cardboard(new double[] {3}, CardboardType.Ball));
                add(new Cardboard(new double[] {2, 4}, CardboardType.Tube));
                add(new Cardboard(new double[] {5}, CardboardType.Ball));
                add(new Cardboard(new double[] {3, 6}, CardboardType.Tube));
                add(new Cardboard(new double[] {2, 3, 4}, CardboardType.Rect));
                add(new Cardboard(new double[] {2}, CardboardType.Ball));
                add(new Cardboard(new double[] {1, 2, 3}, CardboardType.Rect));
                add(new Cardboard(new double[] {6, 6, 3}, CardboardType.Rect));
                add(new Cardboard(new double[] {2, 2, 2}, CardboardType.Rect));
                add(new Cardboard(new double[] {7}, CardboardType.Ball));
                add(new Cardboard(new double[] {4, 8}, CardboardType.Tube));
            }
        };

        var elf = new Elf(cardboards);
        elf.sortCardboards();

        System.out.println("Sorted cardboards volume: " + elf.getSortedCardboardsVolume());
        System.out.println(elf.displaySortedCardboards());
    }
}