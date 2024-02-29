#include "GeneticAlgorithm.h"

Individual *GeneticAlgorithm::getRandomParent()
{
	int firstIndex = rand() % _population.size();
	Individual *firstIndividual = _population[firstIndex];

	int secondIndex = rand() % _population.size();
	while (secondIndex == firstIndex)
	{
		secondIndex = rand() % _population.size();
	}

	Individual *secondIndividual = _population[secondIndex];

	if (firstIndividual->getFitness() > secondIndividual->getFitness())
	{
		return firstIndividual;
	}
	return secondIndividual;
}

void GeneticAlgorithm::initPopulation()
{
	for (int i = 0; i < _populationSize; i++)
	{
		std::vector<int> genotype;

		for (size_t j = 0; j < _evaluator->iGetNumberOfBits(); j++)
		{
			genotype.push_back(lRand(_evaluator->iGetNumberOfValues(j)));
		}

		_population.push_back(new Individual(genotype, _evaluator));
	}
}

GeneticAlgorithm::GeneticAlgorithm(int populationSize, float crossProbability, float mutationProbability, CLFLnetEvaluator *evaluator)
{
	_populationSize = populationSize;
	_crossProbability = crossProbability;
	_mutationProbability = mutationProbability;
	_evaluator = evaluator;
}

void GeneticAlgorithm::runAlgorithm(int iterationCount)
{
	initPopulation();

	for (int i = 0; i < iterationCount; i++)
	{
		cout << "Iteration " << i + 1 << "\t Best fitness: " << getBestIndividual()->getFitness() << endl;
		runIteration();
	}
}

void GeneticAlgorithm::runIteration()
{
	vector<Individual *> newPopulation;

	while (newPopulation.size() < _populationSize)
	{
		Individual *firstParent = getRandomParent();
		Individual *secondParent = getRandomParent();

		if (dRand() < _crossProbability)
		{
			vector<Individual *> crossChildren = firstParent->crossover(*secondParent);

			for (auto child : crossChildren)
			{
				newPopulation.push_back(child);
			}
		}
		else
		{
			newPopulation.push_back(firstParent);
			newPopulation.push_back(secondParent);
		}

		if (dRand() < _mutationProbability)
		{
			int randomIndex = lRand(_populationSize);
			Individual randomIndividual = *_population[randomIndex];

			std::vector<Individual *> mutatedNewPopulation = randomIndividual.przewoMutate();

			for (auto mutatedIndividual : mutatedNewPopulation)
			{
				newPopulation.push_back(mutatedIndividual);
			}
		}
	}

	newPopulation.resize(_populationSize);

	_population = newPopulation;
	cout << _population.size() << endl;
}

Individual *GeneticAlgorithm::getBestIndividual()
{
	Individual *bestIndividual = _population[0];

	for (auto individual : _population)
	{
		if (individual->getFitness() > bestIndividual->getFitness())
		{
			bestIndividual = individual;
		}
	}

	return bestIndividual;
}
