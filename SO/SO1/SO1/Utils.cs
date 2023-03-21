namespace SO1; 

public static class Utils {
    public static bool IsAnyProcessWaiting(List<Process> processList, int tick) {
        foreach (var process in processList) {
            if (process.ArrivalTime <= tick) {
                return true;
            }
        }

        return false;
    }
}