#pragma once
#include "Individual.h"

class GeneticAlgorithm
{
private:
	int _populationSize;
	float _crossProbability;
	float _mutationProbability;

	vector<Individual *> _population;
	CLFLnetEvaluator *_evaluator;

	Individual *getRandomParent();
	void initPopulation();
public:
	GeneticAlgorithm(int populationSize, float crossProbability, float mutationProbability, CLFLnetEvaluator *evaluator);
	void runAlgorithm(int iterationCount);
	void runIteration();
	Individual *getBestIndividual();
};
