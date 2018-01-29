#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm() {
	GeneticAlgorithm(40, 100, 25);
}

GeneticAlgorithm::GeneticAlgorithm(int populationSize, int generations, int mutationRate) {
	POPULATION_SIZE = populationSize;
	GENERATIONS = generations;
	MUTATION_RATE = mutationRate;
}

void GeneticAlgorithm::initate(Chromosome *population, MRC pc, int max, int min) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		Cylinder newCyl;

		newCyl.generateRandom(max, min);
		population[i].candidate = newCyl;
		population[i].fitnessScore = FLT_MAX;
	}
}

void GeneticAlgorithm::evaluate(Chromosome *population, MRC pc) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		float mse = population[i].candidate.calculateMeanSquaredError(pc);
		float intErr = population[i].candidate.calculateInternalBarrelError(pc);
		//float extErr = population[i].cy.calculateBarrelError(pc);
		//population[i].fitness = mse + intErr + extErr;
		population[i].fitnessScore = mse + intErr;
	}

	std::sort(population, population + POPULATION_SIZE);
}
