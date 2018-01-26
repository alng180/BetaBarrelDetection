#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Cylinder.h"
#include "MRC.h"

class Chromosome {
public:
	Cylinder candidate;
	float fitnessScore;

	bool operator<(const Chromosome &other) {
		return fitnessScore < other.fitnessScore;
	}
};

class GeneticAlgorithm {
	public:
		int POPULATION_SIZE;
		int GENERATIONS;
		int MUTATIONS;

		GeneticAlgorithm();
		GeneticAlgorithm(int popsize, int generations, int mutationRate);

		void initate(Chromosome* population, MRC mrc, int max, int min);
		void evaluate(Chromosome* population, MRC mrc);
	private:
};

#endif