#include "Vector3.h"

Vector3::Vector3() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3::Vector3(double nx, double ny, double nz) {
	x = nx;
	y = ny;
	z = nz;
}

bool Vector3::operator== (const Vector3 &other) {
	return (other.x == x) && (other.y == y) && (other.z == z);
}


Vector3 Vector3::operator+ (const Vector3 &other) {
	Vector3 newVec;

	newVec.x = x + other.x;
	newVec.y = y + other.y;
	newVec.z = z + other.z;

	return newVec;
}

Vector3 Vector3::operator- (const Vector3 &other) {
	Vector3 newVec;

	newVec.x = x - other.x;
	newVec.y = y - other.y;
	newVec.z = z - other.z;

	return newVec;
}

Vector3 Vector3::operator* (const float &coeff) {
	Vector3 newVec;

	newVec.x = x * coeff;
	newVec.y = y * coeff;
	newVec.z = z * coeff;

	return newVec;
}

Vector3 Vector3::operator/ (const float &coeff) {
	Vector3 newVec;

	newVec.x = x / coeff;
	newVec.y = y / coeff;
	newVec.z = z / coeff;

	return newVec;
}

double Vector3::dotProduct(const Vector3 &other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

double Vector3::getDotProduct(const Vector3 &left, const Vector3 &right) {
	return (left.x * right.x) + (left.y * right.y) * (left.z * right.z);
}

Vector3 Vector3::crossProduct(const Vector3 &other) {
	Vector3 newVec;

	newVec.x = y * other.z - z * other.y;
	newVec.y = z * other.x - x * other.z;
	newVec.z = x * other.y - y * other.x;

	return newVec;
}

Vector3 Vector3::getCrossProduct(const Vector3 &left, const Vector3 &right) {
	Vector3 newVec;

	newVec.x = left.y * right.z - left.z * right.y;
	newVec.y = left.z * right.x - left.x * right.z;
	newVec.z = left.x * right.y - left.y * right.x;

	return newVec;
}

float Vector3::distance(const Vector3 &other)
{
	double dx = other.x - x;
	double dy = other.y - y;
	double dz = other.z - z;
	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

float Vector3::getDistance(const Vector3 &left, const Vector3 &right) {
	double dx = right.x - left.x;
	double dy = right.y - left.y;
	double dz = right.z - left.z;
	return (float)sqrt(dx * dx + dy * dy + dz * dz);
}