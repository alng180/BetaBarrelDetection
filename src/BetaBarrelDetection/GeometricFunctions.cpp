#include "GeometricFunctions.h"

double GeometricFunctions::getDotProduct(Vector3 left, Vector3 right) {
	return (left.x * right.x) + (left.y * right.y) + (left.z + right.z);
}

Vector3 GeometricFunctions::getCrossProduct(Vector3 left, Vector3 right) {
	Vector3 newVec;

	newVec.x = left.y * right.z - left.z * right.y;
	newVec.y = left.z * right.x - left.x * right.z;
	newVec.z = left.x * right.y - left.y * right.x;

	return newVec;
}

float GeometricFunctions::getDistance(Vector3 left, Vector3 right) {
	double dx = right.x - left.x;
	double dy = right.y - left.y;
	double dz = right.z - left.z;
	return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 GeometricFunctions::getVectorProjection(Vector3 origin, Vector3 firstPt, Vector3 secondPt) {
	Vector3 bVector = firstPt - origin;
	Vector3 aVector = secondPt - origin;

	float bDistance = getDistance(firstPt, origin);

	double dotAB = getDotProduct(aVector, bVector);
	double dotBB = getDotProduct(bVector, bVector);

	return bVector * (dotAB / dotBB) + origin;
}

// OLD USING ROTATION MATRIX
//	rotationAxis and vec must be normalized!
//	resulting vector will be normalized as well!
//Vector3 GeometricFunctions::rotateAroundVector(double theta, Vector3 rotationAxis, Vector3 vec) {
//	double mat[3][3];
//
//	double cosTheta = cos(theta);
//	double sinTheta = sin(theta);
//	double minusCosTheta = 1.0 - cosTheta;
//
//	mat[0][0] = cosTheta + rotationAxis.x * rotationAxis.x * minusCosTheta;
//	mat[0][1] = rotationAxis.x * rotationAxis.y * minusCosTheta - rotationAxis.z * sinTheta;
//	mat[0][2] = rotationAxis.x * rotationAxis.z * minusCosTheta + rotationAxis.y * sinTheta;
//	mat[1][0] = rotationAxis.y * rotationAxis.x * minusCosTheta + rotationAxis.z * sinTheta;
//	mat[1][1] = cosTheta + rotationAxis.y * rotationAxis.y * minusCosTheta;
//	mat[1][2] = rotationAxis.y * rotationAxis.z * minusCosTheta - rotationAxis.x * sinTheta;
//	mat[2][0] = rotationAxis.z * rotationAxis.x * minusCosTheta - rotationAxis.y * sinTheta;
//	mat[2][1] = rotationAxis.z * rotationAxis.y * minusCosTheta + rotationAxis.x * sinTheta;
//	mat[2][2] = cosTheta + rotationAxis.z * rotationAxis.z * minusCosTheta;
//
//	Vector3 result;
//
//	result.x = mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z;
//	result.y = mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z;
//	result.z = mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z;
//
//	return result;
//}

// using rodrigues' rotation equation
Vector3 GeometricFunctions::rotateAroundVector(double theta, Vector3 rotationAxis, Vector3 vec) {

}