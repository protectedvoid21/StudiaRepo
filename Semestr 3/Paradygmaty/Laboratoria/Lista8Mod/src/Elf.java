import Utils.ListUtils;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class Elf
{
    private ArrayList<ArrayList<Cardboard>> _cardboards;

    public Elf(ArrayList<Cardboard> cardboards)
    {
        _cardboards = ListUtils.putListsInList(cardboards);
    }

    public void sortCardboards()
    {
        _cardboards.sort((a, b) ->
        {
            var aVolume = a.getFirst().getVolume();
            var bVolume = b.getFirst().getVolume();
            return Double.compare(aVolume, bVolume);
        });

        ArrayList<Cardboard> cardboardsList = new ArrayList<>(_cardboards.stream()
                .flatMap(Collection::stream)
                .sorted((a, b) -> Double.compare(b.getVolume(), a.getVolume()))
                .toList());

        ArrayList<Cardboard> biggestCardboard = new ArrayList<>(List.of(cardboardsList.removeFirst()));

        var sortedCardboards = new ArrayList<ArrayList<Cardboard>>();
        sortedCardboards.add(biggestCardboard);
        
        for (var cardboard : cardboardsList)
        {
            var fittingInsideCuboidVolume = cardboard.getBiggestFittingInsideCuboid().getVolume();
            var fittingOutsideCuboidVolume = cardboard.getSmallestFittingOutsideCuboid().getVolume();
            
            boolean isPutInside = false;

            for(var sortedCardboardList : sortedCardboards)
            {
                var baseCardboardFittingInsideCuboidVolume = sortedCardboardList.getLast().getBiggestFittingInsideCuboid().getVolume();

                if (fittingInsideCuboidVolume <= baseCardboardFittingInsideCuboidVolume)
                {
                    sortedCardboardList.add(cardboard);
                    isPutInside = true;
                    break;
                }
            }
            
            if(!isPutInside)
            {
                sortedCardboards.add(new ArrayList<>(List.of(cardboard)));
            }
        }
        
        _cardboards = sortedCardboards;
    }

    public ArrayList<ArrayList<Cardboard>> getCardboards()
    {
        return _cardboards;
    }

    public double getSortedCardboardsVolume()
    {
        return _cardboards.stream()
                .mapToDouble(cardboardList -> cardboardList.getFirst().getVolume())
                .sum();
    }
    
    public String displaySortedCardboards()
    {
        var stringBuilder = new StringBuilder();
        
        for(var cardboardList : _cardboards)
        {
            for(var cardboard : cardboardList)
            {
                stringBuilder.append("[" + cardboard.toString() + "]");
            }
            
            stringBuilder.append("\n");
        }
        
        return stringBuilder.toString();
    }
}
