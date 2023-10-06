namespace SO4; 

public class PauseBiggestProcessStrategy : IPauseAlgorithmStrategy {
    public Process PauseProcess(IEnumerable<Process> processes) {
        return processes.MaxBy(p => p.MemorySize);
    }
}