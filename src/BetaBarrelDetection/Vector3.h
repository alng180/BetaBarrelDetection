#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class Vector3 {
public:
	double x;
	double y;
	double z;

	//bool nullVector;

	// constructors
	Vector3();
	Vector3(double nx, double ny, double nz);

	// operator overloads
	bool operator==(const Vector3 &other);
	Vector3 operator- (const Vector3 &other);
	Vector3 operator+ (const Vector3 &other);
	Vector3 operator/ (const float &coeff);
	Vector3 operator* (const float &coeff);

	// vector vector functions
	double dotProduct(const Vector3 &other);
	Vector3 crossProduct(const Vector3 &other);
	float distance(const Vector3 &other);

	// vector functions
	void normalize();

	// static vector functions
	static double getDotProduct(const Vector3 &left, const Vector3 &right);
	static Vector3 getCrossProduct(const Vector3 &left, const Vector3 &right);
	static float getDistance(const Vector3 &left, const Vector3 &right);
	static Vector3 normalizeVector(const Vector3 &vec);
};

#endif