#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Cylinder.h"

class Chromosome {
public:
	Cylinder cyl;
	float fitnessScore;

	bool operator<(const Chromosome &other) {
		return fitnessScore < other.fitnessScore;
	}
};

#endif