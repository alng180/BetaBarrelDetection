#include "MRC.h"

void MRC::createCube(short nX, short nY, short nZ) {
	slcLen = nX * nY;

	data.resize(nX);

	for (int x = 0; x < nX; x++) {
		data[x].resize(nY);

		for (int y = 0; y < nY; y++) {
			data[x][y].resize(nZ);
		}
	}

	sizeOfVxl = sizeof(data[0][0][0]);
}

void MRC::readFile(std::string fileName, double threshold) {
	std::ifstream ifs;
	voxelCount = 0;
	voxels = std::vector<MRCVoxel>();

	ifs.open(fileName.c_str(), std::ios::binary);
	ifs.read((char*)(&header), sizeof(MRC_HEADER));

	createCube(header.nx, header.ny, header.nz);

	for (int iDepth = 0; iDepth < header.nz; iDepth++) {
		for (int iCol = 0; iCol < header.ny; iCol++) {
			for (int iRow = 0; iRow < header.nx; iRow++) {
				ifs.read((char*)&data[iRow][iCol][iDepth], sizeOfVxl);
				if (data[iRow][iCol][iDepth] > threshold) {
					MRCVoxel n = MRCVoxel(iRow + header.xorigin, iCol + header.yorigin, iDepth + header.zorigin, data[iRow][iCol][iDepth] / header.amax);
					voxels.push_back(n);
					voxelCount++;
				}
			}
		}
	}

	ifs.close();
}

std::vector<Vector3> MRC::outputVectors() {
	std::vector<Vector3> outputNodes = std::vector<Vector3>();
	for (int i = 0; i < voxelCount; i++) {
		Vector3 temp = voxels.at(i).position;
		outputNodes.push_back(temp);
	}

	return outputNodes;
}