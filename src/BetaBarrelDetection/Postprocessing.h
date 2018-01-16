#ifndef POSTPROC_H
#define POSTPROC_H

#include <vector>
#include <tuple>

#include "Vector3.h"
#include "Cylinder.h"
#include "GeometricFunctions.h"
#include "RayTrace.h"

class Postprocessing {
	static std::vector<std::tuple<Vector3, std::vector<Vector3>>> calculateCylinderRays(Cylinder cy, int slices, int rays);
	static std::vector<Vector3> findBarrelfromSlice(std::tuple<Vector3, std::vector<Vector3>> slicePtList);
};

#endif