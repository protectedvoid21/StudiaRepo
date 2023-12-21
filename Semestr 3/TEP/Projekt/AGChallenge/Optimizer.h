#pragma once

#include "Evaluator.h"

#include <random>
#include <vector>

using namespace std;

class Optimizer
{
public:
	Optimizer(LFLNetEvaluator &cEvaluator);

	void initialize();
	void runIteration();

	vector<int> *getCurrentBest() { return &v_current_best; }

private:
	void v_fill_randomly(vector<int> &vSolution);

	LFLNetEvaluator &c_evaluator;

	double d_current_best_fitness;
	vector<int> v_current_best;

	mt19937 c_rand_engine;
};//class COptimizer