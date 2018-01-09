#include "Cylinder.h"
#include <random>

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

Cylinder Cylinder::generateRandom(int max, int min) {
	Cylinder cy;

	cy.p1.x = rand() % max + min;
	cy.p1.y = rand() % max + min;
	cy.p1.z = rand() % max + min;
	cy.p2.x = rand() % max + min;
	cy.p2.x = rand() % max + min;
	cy.p2.x = rand() % max + min;

	cy.radius = rand() % MAX_RADIUS;
	if (cy.radius < MIN_RADIUS) cy.radius = MIN_RADIUS;
	//get length
	return cy;
}