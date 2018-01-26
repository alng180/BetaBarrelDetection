#include "Preprocessing.h"

MRC Preprocessing::loadHelicesMRC(std::string mrcFile, double threshold) {
	MRC pc;

	pc.readFile(mrcFile, threshold);

	return pc;
}

MRC Preprocessing::cleanUpHelicesMRC(MRC original, MRC helices) {
	std::vector<Vector3> mainNodes = original.outputVectors();
	std::vector<Vector3> helixNodes = helices.outputVectors();
	std::set<Vector3> helixPositions = std::set<Vector3>(helixNodes.begin(), helixNodes.end());

	MRC newPc = original;
	std::set<MRCVoxel> removedNodes = std::set<MRCVoxel>();

	for (int i = 0; i < helixNodes.size(); i++) {
		Vector3 helixVec = helixNodes.at(i);

		for (int j = 0; j < original.voxels.size(); j++) {
			MRCVoxel node = original.voxels.at(j);
			float dist = GeometricFunctions::getDistance(helixVec, node.position);

			if (dist < 2.0f) {
				removedNodes.insert(node);
			}
		}
	}

	std::vector<MRCVoxel> output = std::vector<MRCVoxel>();

	for (int i = 0; i < original.voxelCount; i++) {
		MRCVoxel node = original.voxels.at(i);

		if (removedNodes.find(node) == removedNodes.end()) {
			output.push_back(node);
		}
	}

	newPc.voxels = output;
	newPc.voxelCount = output.size();

	return newPc;
}

MRC Preprocessing::cleanUpIsolatedClusters(MRC pc) {
	MRC newPc = pc;

	std::set<MRCVoxel> removedNodes = std::set<MRCVoxel>();
	std::set<MRCVoxel> visitedNodes = std::set<MRCVoxel>();

	std::set<MRCVoxel> currentGroup;
	std::queue<MRCVoxel> currQueue;

	for (int i = 0; i < pc.voxelCount; i++) {
		MRCVoxel currNode = pc.voxels.at(i);
		int abc;

		if (visitedNodes.find(currNode) != visitedNodes.end()) {
			continue;
		}

		currQueue.push(currNode);
		currentGroup.insert(currNode);

		while (!currQueue.empty()) {
			MRCVoxel tempNode = currQueue.front();
			currQueue.pop();

			if (visitedNodes.find(tempNode) != visitedNodes.end()) {
				continue;
			}

			visitedNodes.insert(tempNode);
			std::vector<MRCVoxel> nearestNodes = findAllNodesWithinDistance(pc, tempNode, MINDISTANCE);

			for (int j = 0; j < nearestNodes.size(); j++) {
				MRCVoxel tempNode = nearestNodes.at(j);

				if (visitedNodes.find(tempNode) == visitedNodes.end()) {
					currQueue.push(tempNode);
				}

				currentGroup.insert(tempNode);
			}
		}

		if (currentGroup.size() < MINGROUPSIZE) {
			std::vector<MRCVoxel> tempVec = std::vector<MRCVoxel>(currentGroup.begin(), currentGroup.end());
			for (int k = 0; k < tempVec.size(); k++) {
				removedNodes.insert(tempVec.at(k));
			}
		}

		currentGroup.clear();
	}

	std::vector<MRCVoxel> newNodes = std::vector<MRCVoxel>();

	for (int l = 0; l < pc.voxelCount; l++) {
		MRCVoxel currNode = pc.voxels.at(l);

		if (removedNodes.find(currNode) == removedNodes.end()) {
			newNodes.push_back(currNode);
		}
	}

	newPc.voxels = newNodes;
	newPc.voxelCount = newNodes.size();

	return newPc;
}

int Preprocessing::findMax(MRC pc) {
	int max = 0;

	for (int i = 0; i < pc.voxelCount; i++) {
		Vector3 position = pc.voxels.at(i).position;

		int tempMax = std::max({ position.x, position.y, position.z });

		if (tempMax > max) {
			max = tempMax;
		}
	}

	return max;
}

int Preprocessing::findMin(MRC pc) {
	int min = INT_MAX;

	for (int i = 0; i < pc.voxelCount; i++) {
		Vector3 position = pc.voxels.at(i).position;

		int tempMin = std::min({ position.x, position.y, position.z });

		if (tempMin < min) {
			min = tempMin;
		}
	}

	return min;
}

MRCVoxel Preprocessing::findClosestNode(MRC pc, MRCVoxel node) {
	double dist = INT_MAX;
	MRCVoxel closestNode;

	for (int i = 0; i < pc.voxelCount; i++) {
		MRCVoxel currNode = pc.voxels.at(i);

		float distance = GeometricFunctions::getDistance(node.position, currNode.position);

		if (dist > distance) {
			dist = distance;
			closestNode = currNode;
		}
	}

	return closestNode;
}

std::vector<std::string> Preprocessing::splitString(std::string s, char delimiter) {
	std::vector<std::string> output;

	std::stringstream ss;
	ss.str(s);
	std::string item;

	while (std::getline(ss, item, delimiter)) {
		if (item != "") {
			output.push_back(item);
		}
	}

	return output;
}


std::vector<MRCVoxel> Preprocessing::findAllNodesWithinDistance(MRC pc, MRCVoxel node, double minDistance) {
	std::vector<MRCVoxel> allPoints = pc.voxels;
	std::vector<MRCVoxel> output = std::vector<MRCVoxel>();

	for (int i = 0; i < pc.voxelCount; i++) {
		MRCVoxel curr = allPoints.at(i);

		float distance = GeometricFunctions::getDistance(curr.position, node.position);

		if (distance < minDistance) {
			output.push_back(curr);
		}
	}

	return output;
}