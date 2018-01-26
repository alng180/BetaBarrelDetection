#ifndef POSTPROC_H
#define POSTPROC_H

#include <vector>
#include <tuple>
#include <amp.h>
#include <amp_math.h>

#include "Vector3.h"
#include "Cylinder.h"
#include "GeometricFunctions.h"
#include "Vector3_AMP.h"

#define MAX_DISTANCE_FROM_RAY 0.5f

class Postprocessing_AMP {
public:
	std::vector<std::tuple<Vector3, std::vector<Vector3>>> Postprocessing_AMP::calculateCylinderRays(Cylinder cy, int slices, int rays) {
		std::vector<std::tuple<Vector3, std::vector<Vector3>>> raysSliceList = std::vector<std::tuple<Vector3, std::vector<Vector3>>>();

		Vector3 dir = cy.p2 - cy.p1;
		Vector3 ranDir(rand(), rand(), rand());
		ranDir.normalize();

		float cylinderLength = GeometricFunctions::getDistance(cy.p1, cy.p2);
		float sliceLength = cylinderLength / slices;

		for (int slice = 0; slice <= slices; slice++) {
			Vector3 spinePt = cy.p1 + dir * (slices * sliceLength);
			std::vector<Vector3> rotateList = std::vector<Vector3>();

			for (int ray = 0; ray < rays; ray++) {
				Vector3 rotVec = GeometricFunctions::rotateAroundVector(rays * (360 / rays), ranDir, dir);
				Vector3 rotatePt = spinePt + rotatePt * cy.radius;
				rotateList.push_back(rotatePt);
			}

			std::tuple<Vector3, std::vector<Vector3>> sliceTuple(spinePt, rotateList);
			raysSliceList.push_back(sliceTuple);
		}

		return raysSliceList;
	}

	std::vector<Vector3> Postprocessing_AMP::findBarrelfromSlice(MRC pc, std::tuple<Vector3, std::vector<Vector3>> slicePtList) {
		Vector3 origin = std::get<0>(slicePtList);
		std::vector<Vector3> rotates = std::get<1>(slicePtList);
		int size = rotates.size();
		std::vector<AMP_Vector> results_amp = std::vector<AMP_Vector>(rotates.size());

		std::vector<double> rotates_x = std::vector<double>(size);
		std::vector<double> rotates_y = std::vector<double>(size);
		std::vector<double> rotates_z = std::vector<double>(size);

		for (int i = 0; i < size; ++i) {
			Vector3 a = rotates.at(i);
			rotates_x[i] = a.x;
			rotates_y[i] = a.y;
			rotates_z[i] = a.z;
		}

		concurrency::array_view<const MRCVoxel, 1> mrc(pc.voxelCount, pc.voxels);
		concurrency::array_view<int> voxelCount(pc.voxelCount);
		concurrency::array_view<double> ori_x(origin.x);
		concurrency::array_view<double> ori_y(origin.y);
		concurrency::array_view<double> ori_z(origin.z);
		concurrency::array_view<double, 1> rot_x(size, rotates_x);
		concurrency::array_view<double, 1> rot_y(size, rotates_y);
		concurrency::array_view<double, 1> rot_z(size, rotates_z);
		concurrency::array_view<AMP_Vector, 1> res(size, results_amp);
		res.discard_data();

		concurrency::parallel_for_each(res.extent, [=](concurrency::index<1> idx) restrict(amp)
		{
			res[idx] = TraceRay_AMP(mrc, voxelCount[0], ori_x[0], ori_y[0], ori_z[0], rot_x[idx], rot_y[idx], rot_z[idx]);
		}
		);

		res.synchronize();

		std::vector<Vector3> results = std::vector<Vector3>();
		for (int i = 0; i < size; i++) {
			AMP_Vector amp = res[i];

			if (!amp.null) {
				results.push_back(Vector3(amp.x, amp.y, amp.z));
			}
		}

		return results;
	}
private:
	AMP_Vector Postprocessing_AMP::TraceRay_AMP(concurrency::array_view<const MRCVoxel, 1> mrc, int voxelCount, double ori_x, double ori_y, double ori_z, double tra_x, double tra_y, double tra_z) restrict(amp) {
		AMP_Vector ray(tra_x, tra_y, tra_z, ori_x, ori_y, ori_z);
		AMP_Vector ori(ori_x, ori_y, ori_z);
		AMP_Vector tra(tra_x, tra_y, tra_z);
		AMP_Vector intersectPt;

		double bestDistance = DBL_MAX;

		for (int i = 0; i < voxelCount; i++) {
			AMP_Vector p(mrc[i].position.x, mrc[i].position.y, mrc[i].position.z);
			AMP_Vector newVec(p.x, p.y, p.z, ori_x, ori_y, ori_z);

			double scalarProj = AMPDotProduct(ray, newVec) / AMPDistance(tra, ori);
			AMP_Vector vectorProj = AMPVectorProjection(ori, tra, p);
			double distanceFromRay = AMPDistance(vectorProj, p);
			double vectorDistance = AMPDistance(ori, vectorProj);

			if (distanceFromRay > MAX_DISTANCE_FROM_RAY || scalarProj < 0) {
				continue;
			}

			if (vectorDistance < bestDistance) {
				intersectPt = p;
				bestDistance = vectorDistance;
			}
		}

		if (bestDistance != DBL_MAX) {
			return intersectPt;
		}
		else {
			return AMP_Vector(true);
		}
	}

	double Postprocessing_AMP::AMPDotProduct(AMP_Vector left, AMP_Vector right) restrict(amp) {
		return (left.x * right.x) + (left.y * right.y) + (left.z + right.z);
	}

	double Postprocessing_AMP::AMPDistance(AMP_Vector left, AMP_Vector right) restrict(amp) {
		double dx = right.x - left.x;
		double dy = right.y - left.y;
		double dz = right.z - left.z;
		return (double)concurrency::precise_math::sqrt(dx * dx + dy * dy + dz * dz);
	}

	AMP_Vector Postprocessing_AMP::AMPVectorProjection(AMP_Vector origin, AMP_Vector firstPt, AMP_Vector secondPt) restrict(amp) {
		AMP_Vector bVector = firstPt - origin;
		AMP_Vector aVector = secondPt - origin;

		float bDistance = AMPDistance(firstPt, origin);

		double dotAB = AMPDotProduct(aVector, bVector);
		double dotBB = AMPDotProduct(bVector, bVector);

		return bVector * (dotAB / dotBB) + origin;
	}

};

#endif