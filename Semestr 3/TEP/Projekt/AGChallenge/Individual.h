#pragma once
#include <string>
#include <vector>

#include "Evaluator.h"

class Individual
{
	std::vector<int> _genotype;
	CLFLnetEvaluator *_evaluator;
	float *_fitness;

public:
	Individual(vector<int> genotype, CLFLnetEvaluator *evaluator);
	double getFitness();
	void mutate(float mutationProbability);
	std::vector<Individual> crossover(const Individual &other);
};