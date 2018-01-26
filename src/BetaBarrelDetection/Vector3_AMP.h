#ifndef VECTOR3AMP_H
#define VECTOR3AMP_H

struct AMP_Vector {
	double x;
	double y;
	double z;
	double null;

	AMP_Vector() restrict(cpu, amp) {
		x = 0.0;
		y = 0.0;
		z = 0.0;
		null = false;
	}

	AMP_Vector(double nx, double ny, double nz) restrict(amp) {
		x = nx;
		y = ny;
		z = nz;
		null = false;
	}

	AMP_Vector(double x1, double y1, double z1, double x2, double y2, double z2) restrict(amp) {
		x = x2 - x1;
		y = y2 - y1;
		z = z2 - z1;
		null = false;
	}

	AMP_Vector(const AMP_Vector &other) restrict(cpu, amp) {
		x = other.x;
		y = other.y;
		z = other.z;
		null = other.null;
	}

	AMP_Vector(bool xnull) restrict(amp) {
		x = 0.0;
		y = 0.0;
		z = 0.0;
		null = xnull;
	}

	AMP_Vector operator+ (const AMP_Vector &other) restrict(amp) {
		AMP_Vector newVec;

		newVec.x = x + other.x;
		newVec.y = y + other.y;
		newVec.z = z + other.z;

		return newVec;
	}

	AMP_Vector operator- (const AMP_Vector &other) restrict(amp) {
		AMP_Vector newVec;

		newVec.x = x - other.x;
		newVec.y = y - other.y;
		newVec.z = z - other.z;

		return newVec;
	}

	AMP_Vector operator* (const double &coeff) restrict(amp) {
		AMP_Vector newVec;

		newVec.x = x * coeff;
		newVec.y = y * coeff;
		newVec.z = z * coeff;

		return newVec;
	}
};

#endif