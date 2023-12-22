#include "Optimizer.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;

Optimizer::Optimizer(LFLNetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());

	d_current_best_fitness = 0;
}//COptimizer::COptimizer(CEvaluator &cEvaluator)

void Optimizer::initialize()
{
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();
}//void COptimizer::vInitialize()

void Optimizer::runIteration()
{
	vector<int> v_candidate;
	v_fill_randomly(v_candidate);

	double d_candidate_fitness = c_evaluator.evaluate(&v_candidate);

	if (d_candidate_fitness > d_current_best_fitness)
	{
		v_current_best = v_candidate;
		d_current_best_fitness = d_candidate_fitness;

		cout << d_current_best_fitness << endl;
	}//if (d_candidate_fitness > d_current_best_fitness)
}//void COptimizer::vRunIteration()



void Optimizer::v_fill_randomly(vector<int> &vSolution)
{
	vSolution.resize((size_t)c_evaluator.getNumberOfBits());

	for (int ii = 0; ii < vSolution.size(); ii++)
	{
		vSolution.at(ii) = lRand(c_evaluator.getNumberOfValues(ii));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void COptimizer::v_fill_randomly(const vector<int> &vSolution)
