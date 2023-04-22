using SO3;
using SO3.Algorithms;

namespace Tests;

public class AlgorithmTests {
    public static IEnumerable<object[]> FIFOData() {
        yield return new object[] { new[] { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 1, 5, 5 }, 4, 10 };
        yield return new object[] { new[] { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 }, 3, 9 };
        yield return new object[] { new[] { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 }, 4, 10 }; 
    }
    
    public static IEnumerable<object[]> LRUData() {
        yield return new object[] { new[] { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 1, 5, 5 }, 4, 8 };
    }
    
    public static IEnumerable<object[]> ALRUData() {
        yield return new object[] { new[] { 1,2,3,4,5,3,1,5,2 }, 4, 7 };
        yield return new object[] { new[] { 1,2,3,4,1,2,5,1,2,3,4,1,5,5 }, 4, 10 };
    }

    [Theory]
    [MemberData(nameof(FIFOData))]
    public void Check_CorrectInfo_FIFOAlgorithm(int[] requests, int pageCount, int expectedFailures) {
        var pages = Generator.GetPages(pageCount);
        FIFOAlgorithm fifo = new(pages, requests, "...");

        fifo.Execute();

        Assert.Equal(expectedFailures, fifo.FailureCount);
    }


    [Theory]
    [MemberData(nameof(LRUData))]
    public void Check_CorrectInfo_LRUAlgorithm(int[] requests, int pageCount, int expectedFailures) {
        var pages = Generator.GetPages(pageCount);
        LRUAlgorithm lru = new(pages, requests, "...");

        lru.Execute();

        Assert.Equal(expectedFailures, lru.FailureCount);
    }
    
    [Theory]
    [MemberData(nameof(ALRUData))]
    public void Check_CorrectInfo_ALRUAlgorithm(int[] requests, int pageCount, int expectedFailures) {
        var pages = Generator.GetPages(pageCount);
        ALRUAlgorithm alru = new(pages, requests, "...");

        alru.Execute();

        Assert.Equal(expectedFailures, alru.FailureCount);
    }
}