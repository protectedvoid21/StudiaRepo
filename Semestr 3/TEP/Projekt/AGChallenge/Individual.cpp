#include "Individual.h"

#include "Evaluator.h"

Individual::Individual(const vector<int> &genotype, CLFLnetEvaluator *evaluator) : _genotype(genotype), _evaluator(evaluator), _fitness(nullptr)
{ }

double Individual::getFitness()
{
	if (_fitness == nullptr)
	{
		return _evaluator->dEvaluate(&_genotype);
	}
	return *_fitness;
}

void Individual::mutate(float mutationProbability)
{
	for (int i = 0; i < _genotype.size(); i++)
	{
		if (dRand() < mutationProbability)
		{
			_genotype[i] = lRand(_evaluator->iGetNumberOfValues(i));
		}
	}
}

std::vector<Individual *> Individual::crossover(const Individual &other)
{
	const int crossoverPoint = iRand() % (_genotype.size() - 1) + 1;

	std::vector<int> genotype1(_genotype.begin(), _genotype.begin() + crossoverPoint);
	std::vector<int> genotype2(other._genotype.begin(), other._genotype.begin() + crossoverPoint);

	genotype1.insert(genotype1.end(), other._genotype.begin() + crossoverPoint, other._genotype.end());
	genotype2.insert(genotype2.end(), _genotype.begin() + crossoverPoint, _genotype.end());

	return
	{
		new Individual(genotype1, _evaluator),
		new Individual(genotype2, _evaluator)
	};
}

