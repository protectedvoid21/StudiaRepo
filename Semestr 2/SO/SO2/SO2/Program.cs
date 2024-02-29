﻿using SO2;
using SO2.Algorithms;

public class Program {
    private static void Main() {
        const int cylinderCount = 200;

        List<Request> requestList = new RequestGeneratorBuilder()
            .SetRequests(2500)
            .SetCylinderCount(cylinderCount)
            .SetMinCylinder(1)
            .SetMaxCylinder(200)
            .SetMaxArrivalTime(25000)
            .SetDeadlinePercentage(15)
            .SetMinimumDeadline(40)
            .SetMaximumDeadline(100)
            .Generate();
        
        //List<Request> requestList = RequestGenerator.GenerateCustom(new[] {53, 98,183,37,122,14,124,65,67}, 200);
        //List<Request> requestList = RequestGenerator.GenerateCustom(new[] { 53, 65, 98, 183, 37, 122, 14, 124, 67 }, 200);
        //List<Request> requestList = RequestGenerator.GenerateCustom(new[] {50, 176, 79, 34, 60, 92, 11, 41, 114}.Select(n => n + 1), 200);

        Algorithm[] algorithms = {
            new FCFSAlgorithm(RequestGenerator.CloneRequests(requestList), "FCFS"),
            new SSTFAlgorithm(RequestGenerator.CloneRequests(requestList), "SSTF"),
            new SCANAlgorithm(RequestGenerator.CloneRequests(requestList), "SCAN", cylinderCount),
            new CSCANAlgorithm(RequestGenerator.CloneRequests(requestList), "C-SCAN", cylinderCount),
        };

        List<AlgorithmStats> algorithmStatsList = new();
        
        Console.WriteLine("DISK ACCESS ALGORITHMS SIMULATION");
        foreach (var algorithm in algorithms) {
            Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
            algorithm.Execute();
            algorithmStatsList.Add(new AlgorithmStats(algorithm));
            Console.WriteLine($"[COMPLETED] {algorithm.Name}");
        }
        
        Algorithm[] deadlineAlgorithms = {
            new EDFAlgorithm(RequestGenerator.CloneRequests(requestList), "EDF (+ SSTF)"),
            new FDSCANAlgorithm(RequestGenerator.CloneRequests(requestList), "FD-SCAN")
        };

        List<AlgorithmDeadlineStats> deadlineStatsList = new();

        foreach (var algorithm in deadlineAlgorithms) {
            Console.WriteLine($"[EXECUTING] {algorithm.Name}...");
            algorithm.Execute();
            deadlineStatsList.Add(new AlgorithmDeadlineStats(algorithm));
            Console.WriteLine($"[COMPLETED] {algorithm.Name}");
        }
        
        Console.Clear();
        
        Console.WriteLine();
        AlgorithmAnalizer.Create(algorithmStatsList, cylinderCount);
        
        Console.WriteLine();
        AlgorithmAnalizer.Create(deadlineStatsList, cylinderCount);
        
    }
}