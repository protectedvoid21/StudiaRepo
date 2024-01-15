package Utils;

import java.util.ArrayList;

public class ListUtils
{
    public static <T> ArrayList<ArrayList<T>> putListsInList(ArrayList<T> list)
    {
        var result = new ArrayList<ArrayList<T>>();
        for(var item : list)
        {
            var newList = new ArrayList<T>();
            newList.add(item);

            result.add(newList);
        }

        return result;
    }
}
