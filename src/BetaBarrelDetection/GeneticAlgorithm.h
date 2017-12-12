#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Cylinder.h"

class Chromosome {
public:
	Cylinder candidate;
	float fitnessScore;

	bool operator<(const Chromosome &other) {
		return fitnessScore < other.fitnessScore;
	}
};

class GeneticAlgorithm {

};

#endif