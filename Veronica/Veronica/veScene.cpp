#include "veScene.h"
#include "veUtils.h"

#include <stdio.h>

namespace vee {

	//---------------------------------------------------------------
	Scene::Scene() {
	}

	//---------------------------------------------------------------
	Scene::~Scene() {
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 * @sx {int} x size.
	 * @sy {int} y size.
	 * @sz {int} z size.
	 */
	void Scene::init(int sx, int sy, int sz) {

		// Init chunk
		mChunk.init(sx, sy, sz);
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void Scene::destroy() {
	}


	//---------------------------------------------------------------
	/**
	 * Save to file
	 */
	void Scene::save(char* fileName) {

		/*
		// File
		FILE* fp;

		// Open file
		fopen_s(&fp, fileName, "wb");

		if (!fp) {
			return;
		}


		// Volume
		// World position
		fwrite(mVolume.mPos, sizeof(int), 3, fp);
		// Size
		fwrite(mVolume.mSize, sizeof(int), 3, fp);


		// Chunk volume size
		fwrite(mCVSize, sizeof(int), 3, fp);


		// Current chunk
		Chunk* c;


		// Current voxel
		Voxel* v;

		// Voxel type
		VoxelType vt;


		// Loop each chunk
		for (uint i = 0; i < mChunkArray.size(); i++) {

			// Current chunk
			c = mChunkArray[i];

			// Chunk volume
			// World position
			fwrite(c->mVolume.mPos, sizeof(int), 3, fp);
			// Size
			fwrite(c->mVolume.mSize, sizeof(int), 3, fp);


			// Loop each voxel
			for (int j = 0; j < c->mVolume.mSize[0]*c->mVolume.mSize[1]*c->mVolume.mSize[2]; j++) {

				// Current voxel
				v = c->mData[j];

				if (v) {

					// Voxel type
					fwrite(&v->mType, sizeof(VoxelType), 1, fp);

					// Voxel color
					fwrite(v->mColor, sizeof(uchar), 4, fp);

				} else {

					// Empty voxel type
					vt = VT_AIR;

					fwrite(&vt, sizeof(VoxelType), 1, fp);
				}
			}
		}


		// Close file
		fclose(fp);
		*/
	}

	//---------------------------------------------------------------
	/**
	 * Load from file
	 * @fileName {char*} file name.
	 */
	void Scene::load(char* fileName) {

		/*
		// File
		FILE* fp;

		// Open file
		fopen_s(&fp, fileName, "rb");

		if (!fp) {
			return;
		}


		// Volume
		// World position
		fread(mVolume.mPos, sizeof(int), 3, fp);
		// Size
		fread(mVolume.mSize, sizeof(int), 3, fp);


		// Chunk volume size
		fread(mCVSize, sizeof(int), 3, fp);


		// Current chunk
		Chunk* c;


		// Chunk volume world position
		int vPos[3];

		// Chunk volume size
		int vSize[3];


		// Current voxel
		Voxel* v;

		// Voxel type
		VoxelType vt;


		// Loop each chunk
		for (int i = 0; i < mCVSize[0]*mCVSize[1]*mCVSize[2]; i++) {

			// Chunk volume
			// World position
			fread(vPos, sizeof(int), 3, fp);
			// Size
			fread(vSize, sizeof(int), 3, fp);


			// Current chunk
			c = new Chunk();

			// Init chunk
			c->init(vSize[0], vSize[1], vSize[2], vPos[0], vPos[1], vPos[2]);


			// Loop each voxel
			for (int x = 0; x < vSize[0]; x++) {

				for (int y = 0; y < vSize[1]; y++) {

					for (int z = 0; z < vSize[2]; z++) {

						// Voxel type
						fread(&vt, sizeof(VoxelType), 1, fp);

						if (vt != VT_AIR) {

							// Current voxel
							v = new Voxel();

							// Type
							v->mType = vt;

							// Color
							fread(v->mColor, sizeof(uchar), 4, fp);

						} else {
							
							v = NULL;
						}


						// Set voxel
						c->setVoxel(x, y, z, v);
					}
				}
			}


			// Push chunk to chunk array
			mChunkArray.push_back(c);
		}


		// Close file
		fclose(fp);
		*/
	}


	//---------------------------------------------------------------
	/**
	 * Test world space coordinate inside or not.
	 */
	bool Scene::testInside(int i, int j, int k) {

		return mChunk.mVolume.contain(i, j, k);
	}


	//---------------------------------------------------------------
	/**
	 * Get voxel
	 * @i {int} world space x coordinate.
	 * @j {int} world space y coordinate.
	 * @k {int} world space z coordinate.
	 * @r {Voxel*} result voxel pointer.
	 * @return {bool} voxel inside world or not.
	 */
	bool Scene::getVoxel(int i, int j, int k, Voxel*& r) {

		// Test inside or not
		if (!testInside(i, j, k)) {
			
			return false;
		} else {

			//r = mChunk.getVoxel(i, j, k);

			return true;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Set voxel
	 * @i {int} world space x coordinate.
	 * @j {int} world space y coordinate.
	 * @k {int} world space z coordinate.
	 * @v {Voxel*} voxel data.
	 */
	void Scene::setVoxel(int i, int j, int k, Voxel* v) {

		// Test inside or not
		if (!testInside(i, j, k)) {

			return;
		} else {

			mChunk.setVoxel(i, j, k, v);
		}
	}
};
