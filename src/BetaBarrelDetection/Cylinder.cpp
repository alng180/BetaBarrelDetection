#include "Cylinder.h"

Cylinder::Cylinder() {
	p1 = Vector3();
	p2 = Vector3();
	radius = 0.0;
	length = 0.0;
}

Cylinder::Cylinder(Vector3 first, Vector3 second, double rad) {
	p1 = first;
	p2 = second;
	radius = rad;
	length = Vector3::getDistance(first, second);
}

