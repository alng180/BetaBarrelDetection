#ifndef PREPROC_H
#define PREPROC_H

#include <set>
#include <queue>
#include <cfloat>
#include <sstream>
#include <fstream>
#include <vector>

#include "MRC.h"
#include "GeometricFunctions.h"
#include "Vector3.h"

#define MINDISTANCE 1.0f
#define MINGROUPSIZE 200

class Preprocessing {
public:
	MRC loadHelicesMRC(std::string mrcFile, double threshold);
	MRC cleanUpHelicesMRC(MRC original, MRC helices);
	MRC cleanUpIsolatedClusters(MRC pc);

	int findMin(MRC pc);
	int findMax(MRC pc);
private:
	std::vector<std::string> splitString(std::string s, char delimiter);
	std::vector<MRCVoxel> findAllNodesWithinDistance(MRC pc, MRCVoxel node, double distance);
	MRCVoxel findClosestNode(MRC pc, MRCVoxel node);
};

#endif