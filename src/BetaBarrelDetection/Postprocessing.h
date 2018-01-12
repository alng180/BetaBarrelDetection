#ifndef POSTPROC_H
#define POSTPROC_H

#include <vector>
#include <tuple>

#include "Vector3.h"
#include "Cylinder.h"
#include "GeometricFunctions.h"

class Postprocessing {
	static std::vector<std::tuple<Vector3, std::vector<Vector3>>> calculateCylinderRays(Cylinder cy, int slices, int rays);
};

#endif