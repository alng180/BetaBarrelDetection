#include "Postprocessing.h"

std::vector<std::tuple<Vector3, std::vector<Vector3>>> Postprocessing::calculateCylinderRays(Cylinder cy, int slices, int rays) {
	std::vector<std::tuple<Vector3, std::vector<Vector3>>> raysSliceList = std::vector<std::tuple<Vector3, std::vector<Vector3>>>();
	
	Vector3 dir = cy.p2 = cy.p1;
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