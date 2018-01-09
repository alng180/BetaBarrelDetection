#ifndef GEOFUNC_H
#define GEOFUNC_H

#include "Vector3.h"
#include "MRC.h"

class GeometricFunctions {
private:
public:
	static double getDotProduct(Vector3 left, Vector3 right);
	static Vector3 getCrossProduct(Vector3 left, Vector3 right);
	static float getDistance(Vector3 left, Vector3 right);
	static bool getIntersection(Vector3 first, Vector3 second, Vector3 &result);

	static bool isParallel(Vector3 first, Vector3 second);

	static Vector3 getVectorProjection(Vector3 origin, Vector3 firstPt, Vector3 secondPt);
	static Vector3 rotateAroundVector(double theta, Vector3 rotationAxis, Vector3 vec);

};

#endif