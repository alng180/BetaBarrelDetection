#ifndef RAYTRACE_H
#define RAYTRACE_H

#include <omp.h>
#include <amp.h>
#include <vector>
#include "Vector3.h"
#include "MRC.h"

class RayTracer {
public:
	RayTracer(MRC mrc);

	std::vector<Vector3> findImage(Vector3 spinePt, std::vector<Vector3> rotatedPts);
	Vector3 TraceRay(Vector3 originPt, Vector3 tracePt, bool &intersect);
private:
	MRC pointcloud;
	Vector3 TraceRay_std(Vector3 originPt, Vector3 tracePt, bool &intersect);
	Vector3 TraceRay_CPU(Vector3 originPt, Vector3 tracePt, bool &intersect);
	Vector3 TraceRay_AMP(Vector3 originPt, Vector3 tracePt, bool &intersect);
};

#endif