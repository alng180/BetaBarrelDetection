#ifndef MRC_H
#define MRC_H

#include "Vector3.h"

#include <string>
#include <vector>
#include <fstream>

struct MRCVoxel {
	Vector3 position;
	float density;

	MRCVoxel() : density(0.0), position(Vector3()) {}
	MRCVoxel(float x, float y, float z, float dens) {
		density = dens;
		position = Vector3(x, y, z);
	}
};

// copied from Dr Dong Si's code
struct MRC_HEADER {


	int    nx;            /* # of columns ( fastest changing in the map    */
	int    ny;            /* # of rows                                     */
	int    nz;            /* # of sections (slowest changing in the map    */

	int    mode;          /* data type
						  0 = image data in bytes
						  1 = image data in short integer
						  2 = image data in floats
						  3 = complex data in complex short integers
						  4 = complex data in complex reals          */

	int    nxstart;       /* number of first column in map (default = 0)   */
	int    nystart;       /* number of first row in map (default = 0)      */
	int    nzstart;       /* number of first ssection in map (default = 0) */

	int    mx;            /* number of intervals along X                   */
	int    my;            /* number of intervals along Y                   */
	int    mz;            /* number of intervals along Z                   */

	float  xlength;       /* cell dimensions in X (angstrom)               */
	float  ylength;       /* cell dimensions in Y (angstrom)               */
	float  zlength;       /* cell dimensions in Z (angstrom)               */

	float  alpha;         /* cell angles between Y and Z                   */
	float  beta;          /* cell angles between X and Z                   */
	float  gamma;         /* cell angles between X and Y                   */

	int    mapc;          /* number of axis corresponding to columns (X)   */
	int    mapr;          /* number of axis corresponding to rows (Y)      */
	int    maps;          /* number of axis corresponding to sections (Z)  */

	float  amin;          /* minimum density value                         */
	float  amax;          /* maximum density value                         */
	float  amean;         /* mean density value                            */

	int    ispg;          /* space group number (0 for images)             */
	int    nsymbt;        /* # of bytes for symmetry operators             */

	int    extra[25];     /* user defined storage space                    */

	float  xorigin;       /* X phase origin                                */
	float  yorigin;       /* Y phase origin                                */
	float	 zorigin;		/* Z phase origin								 */

	char map[4];			/* constant string "MAP "						*/

	int machineStamp;		/* machine stamp in ccp4 convention: big endian: 0x11110000, little endian 0x44440000 */

	float rms;			/* rms deviation of map from mean density		*/


	int    nlabl;         /* # of labels being used in the MRC header      */

	char   label[10][80]; /* actual text labels                            */

						  /*
						  * NOTE: In some cases what follows the MRC header are symmetry records stored as
						  *       text as in the International Tables operators. These are separated by
						  *       a * and grouped into 'lines' of 80 characters.
						  */

						  //initializer
	MRC_HEADER() : nx(0), ny(0), nz(0), mode(2), nxstart(0), nystart(0), nzstart(0), mx(0), my(0), mz(0), xlength(0), \
		ylength(0), zlength(0), alpha(0), beta(0), gamma(0), mapc(0), mapr(0), maps(0), amin(0), amax(0), \
		amean(0), ispg(0), nsymbt(0), xorigin(0.0), yorigin(0.0), zorigin(0.0), nlabl(0) {}

};

class MRC {
public:
	MRC_HEADER header;

	std::vector<std::vector<std::vector<float>>> data;
	std::vector<MRCVoxel> voxels;

	int voxelCount;
	
	void readFile(std::string fileName, double threshold);
private:
	short slcLen;
	short sizeOfVxl;

	void createCube(short nX, short nY, short nZ);
};

#endif