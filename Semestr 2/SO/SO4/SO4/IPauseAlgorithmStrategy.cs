namespace SO4; 

public interface IPauseAlgorithmStrategy {
    Process PauseProcess(IEnumerable<Process> processes);
}