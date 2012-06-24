#include "veBoundingBox.h"
#include "veUtils.h"
#include "veVoxel.h"

namespace vee {

	//---------------------------------------------------------------
	Voxel::Voxel() {

		// Type
		mType = VT_DEFAULT;

		// Color
		mColor[0] = 255;
		mColor[1] = 255;
		mColor[2] = 255;
		mColor[3] = 255;
	}

	//---------------------------------------------------------------
	Voxel::Voxel(Voxel& v) {

		// Type
		mType = v.mType;

		// Color
		mColor[0] = v.mColor[0];
		mColor[1] = v.mColor[1];
		mColor[2] = v.mColor[2];
		mColor[3] = v.mColor[3];
	}

	//---------------------------------------------------------------
	Voxel::~Voxel() {
	}


	//---------------------------------------------------------------
	Chunk::Chunk() {

		// Voxel array
		mData = NULL;
	}

	//---------------------------------------------------------------
	Chunk::~Chunk() {

		// Total
		int total = mVolume.mSize[0]*mVolume.mSize[1]*mVolume.mSize[2];

		// Loop each voxel
		for (int i = 0; i < total; i++) {
			
			// Delete voxel
			delete mData[i];
		}

		// Delete pointer array
		delete [] mData;
	}

	//---------------------------------------------------------------
	/**
	 * Init
	 * @sx {int} x size.
	 * @sy {int} y size.
	 * @sz {int} z size.
	 * @px {int} world x pos.
	 * @py {int} world y pos.
	 * @pz {int} world z pos.
	 */
	void Chunk::init(int sx, int sy, int sz, int px, int py, int pz) {

		// Volume
		mVolume.mPos[0] = px;
		mVolume.mPos[1] = py;
		mVolume.mPos[2] = pz;

		mVolume.mSize[0] = sx;
		mVolume.mSize[1] = sy;
		mVolume.mSize[2] = sz;

		// Voxel array
		int total = mVolume.mSize[0]*mVolume.mSize[1]*mVolume.mSize[2];

		// Create pointer array
		mData = new Voxel*[total];

		// Loop each voxel
		for (int i = 0; i < total; i++) {

			// Create voxel
			mData[i] = new Voxel();
		}
	}

	//---------------------------------------------------------------
	/**
	 * This function assumes input coordinate i, j, k is
	 * inside of the volume.
	 *
	 * Get voxel
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 */
	Voxel* Chunk::getVoxel(int i, int j, int k) {
		return mData[Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2])];
	}

	//---------------------------------------------------------------
	/**
	 * This function assumes input coordinate i, j, k is
	 * inside of the volume.
	 *
	 * Set voxel
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @v {Voxel*} input voxel pointer.
	 */
	void Chunk::setVoxel(int i, int j, int k, Voxel* v) {

		// Index
		int index = Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2]);

		if (mData[index]) {

			// Delete the old one
			delete mData[index];
		}

		mData[index] = v;
	}
};