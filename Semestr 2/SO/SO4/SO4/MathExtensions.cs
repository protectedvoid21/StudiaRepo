namespace SO4; 

public static class MathExtensions {
    public static float StandardDeviation(this IEnumerable<int> values) {
        double avg = values.Average();
        return (float)Math.Sqrt(values.Average(v => Math.Pow(v - avg, 2)));
    }
    
    public static float Median(this IEnumerable<int> values) {
        int[] array = values.ToArray();
        if (array.Length % 2 == 0) {
            return (float)(array[array.Length / 2 - 1] + array[array.Length / 2]) / 2;
        }

        return array[array.Length / 2];
    }
}