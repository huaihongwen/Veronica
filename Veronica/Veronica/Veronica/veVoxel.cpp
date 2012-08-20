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
	Voxel::Voxel(VoxelType t, uchar* c) {

		// Type
		mType = t;

		// Color
		mColor[0] = c[0];
		mColor[1] = c[1];
		mColor[2] = c[2];
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

		// Destroy
		destroy();
	}

	//---------------------------------------------------------------
	/**
	 * Init
	 * @c {Chunk&} input chunk.
	 */
	void Chunk::init(Chunk* c) {

		// Volume
		mVolume.mPos[0] = c->mVolume.mPos[0];
		mVolume.mPos[1] = c->mVolume.mPos[1];
		mVolume.mPos[2] = c->mVolume.mPos[2];

		mVolume.mSize[0] = c->mVolume.mSize[0];
		mVolume.mSize[1] = c->mVolume.mSize[1];
		mVolume.mSize[2] = c->mVolume.mSize[2];


		// Voxel array
		int total = mVolume.mSize[0]*mVolume.mSize[1]*mVolume.mSize[2];

		// Create pointer array
		mData = new Voxel*[total];


		int idx;

		// Loop each voxel
		for (int i = 0; i < mVolume.mSize[0]; i++) {
			for (int j = 0; j < mVolume.mSize[1]; j++) {
				for (int k = 0; k < mVolume.mSize[2]; k++) {

					idx = Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2]);

					if (c->mData[idx]) {

						mData[idx] = new Voxel(*(c->mData[idx]));
					} else {

						mData[idx] = NULL;
					}
				}
			}
		}
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


		int idx;

		// Loop each voxel
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					idx = Utils::toArrayIndex(i, j, k, sy, sz);

					//mData[idx] = NULL;
					mData[idx] = new Voxel();
				}
			}
		}
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 * @fileName {char*} file name.
	 */
	void Chunk::init(char* fileName) {

		// File
		FILE* fp;

		// Open file
		fopen_s(&fp, fileName, "rb");

		if (!fp) {
			return;
		}


		// Voxel type
		VoxelType vt;

		// Index
		int idx;


		// Volume
		// World position
		fread(mVolume.mPos, sizeof(int), 3, fp);
		// Size
		fread(mVolume.mSize, sizeof(int), 3, fp);


		// Voxel array
		int total = mVolume.mSize[0]*mVolume.mSize[1]*mVolume.mSize[2];

		// Create pointer array
		mData = new Voxel*[total];


		// Loop each voxel
		for (int i = 0; i < mVolume.mSize[0]; i++) {
			for (int j = 0; j < mVolume.mSize[1]; j++) {
				for (int k = 0; k < mVolume.mSize[2]; k++) {

					// Index
					idx = Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2]);

					// Voxel type
					fread(&vt, sizeof(VoxelType), 1, fp);


					if (vt != VT_AIR) {

						// Voxel
						mData[idx] = new Voxel();

						// Voxel type
						mData[idx]->mType = vt;

						// Voxel color
						fread(mData[idx]->mColor, sizeof(uchar), 4, fp);
					} else {

						mData[idx] = NULL;
					}
				}
			}
		}


		// Close file
		fclose(fp);
	}


	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void Chunk::destroy() {

		if (mData) {

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
	}


	//---------------------------------------------------------------
	/**
	 * Save to file
	 * @fileName {char*} file name.
	 */
	void Chunk::saveToFile(char* fileName) {

		// File
		FILE* fp;

		// Open file
		fopen_s(&fp, fileName, "wb");

		if (!fp) {
			return;
		}


		// Voxel type
		VoxelType vt;


		// Volume
		// World position
		fwrite(mVolume.mPos, sizeof(int), 3, fp);
		// Size
		fwrite(mVolume.mSize, sizeof(int), 3, fp);


		// Loop each voxel
		for (int i = 0; i < mVolume.mSize[0]*mVolume.mSize[1]*mVolume.mSize[2]; i++) {

			if (mData[i]) {

				// Voxel type
				fwrite(&mData[i]->mType, sizeof(VoxelType), 1, fp);

				// Voxel color
				fwrite(mData[i]->mColor, sizeof(uchar), 4, fp);
			} else {

				// Empty voxel type
				vt = VT_AIR;
				fwrite(&vt, sizeof(VoxelType), 1, fp);
			}
		}


		// Close file
		fclose(fp);
	}


	//---------------------------------------------------------------
	/**
	 * Get voxel
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @return {bool} voxel inside or not.
	 */
	bool Chunk::getVoxel(int i, int j, int k, Voxel*& v) {

		// Test inside or not
		if (!mVolume.contain(i, j, k)) {

			return false;
		} else {

			v = mData[Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2])];

			return true;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Set voxel
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @v {Voxel*} input voxel pointer.
	 */
	void Chunk::setVoxel(int i, int j, int k, Voxel* v) {

		// Test inside or not
		if (!mVolume.contain(i, j, k)) {

			return;
		}


		// Index
		int index = Utils::toArrayIndex(i, j, k, mVolume.mSize[1], mVolume.mSize[2]);

		if (mData[index]) {

			// Delete the old one
			delete mData[index];
		}

		mData[index] = v;
	}
};