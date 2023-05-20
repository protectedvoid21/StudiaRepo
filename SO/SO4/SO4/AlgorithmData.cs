namespace SO4; 

public record AlgorithmData(Page[] Pages, List<Process> ProcessList);

public record AlgorithmInitData(List<AlgorithmStats> AlgorithmStats, int ProcessCount, int PageCount, int MaxRequest);