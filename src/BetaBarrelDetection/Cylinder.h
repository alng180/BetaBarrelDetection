#ifndef CYLINDER_H
#define CYLINDER_H

#include "Vector3.h"
#include <omp.h>

#define MAX_RADIUS 10
#define MIN_RADIUS 3

class Cylinder {
public:
	Vector3 p1;
	Vector3 p2;
	double radius;
	double length;

	Cylinder();
	Cylinder(Vector3 first, Vector3 second, double radius);

	static Cylinder generateRandom(int max, int min);
};

#endif