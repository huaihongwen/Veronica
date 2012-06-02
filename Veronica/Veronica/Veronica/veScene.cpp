#include "veScene.h"
#include "veUtils.h"

namespace vee {

	//---------------------------------------------------------------
	Scene::Scene() {
	}

	//---------------------------------------------------------------
	Scene::~Scene() {

		// Loop each chunk
		for (uint i = 0; i < mChunkArray.size(); i++) {

			// Delete chunk
			delete mChunkArray[i];
		}

		// Clear chunk array
		mChunkArray.clear();
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 * @sx {int} x size.
	 * @sy {int} y size.
	 * @sz {int} z size.
	 */
	void Scene::init(int sx, int sy, int sz) {

		// Volume
		mVolume.mPos[0] = 0;
		mVolume.mPos[1] = 0;
		mVolume.mPos[2] = 0;

		mVolume.mSize[0] = sx;
		mVolume.mSize[1] = sy;
		mVolume.mSize[2] = sz;


		// Chunk volume size
		mCVSize[0] = sx / SCENECHUNK_X;
		mCVSize[1] = sy / SCENECHUNK_Y;
		mCVSize[2] = sz / SCENECHUNK_Z;

		// Chunk
		Chunk* c;

		// Loop each chunk
		for (int i = 0; i < mCVSize[0]; i++) {

			for (int j = 0; j < mCVSize[1]; j++) {

				for (int k = 0; k < mCVSize[2]; k++) {

					// Create chunk
					c = new Chunk();

					// Push chunk
					mChunkArray.push_back(c);

					// Init chunk
					c->init(SCENECHUNK_X, SCENECHUNK_Y, SCENECHUNK_Z,
						i*SCENECHUNK_X, j*SCENECHUNK_Y, k*SCENECHUNK_Z);
				}
			}
		}
	}

	//---------------------------------------------------------------
	/**
	 * Get voxel
	 * @i {int} world space x coordinate.
	 * @j {int} world space y coordinate.
	 * @k {int} world space z coordinate.
	 */
	Voxel* Scene::getVoxel(int i, int j, int k) {

		if (!mVolume.contain(i, j, k)) {

			// Outside of world
			return NULL;
		} else {

			// Chunk coordinate
			int ci = (int)(i / SCENECHUNK_X);
			int cj = (int)(j / SCENECHUNK_Y);
			int ck = (int)(k / SCENECHUNK_Z);

			// Chunk space coordinate
			int csi = i % SCENECHUNK_X;
			int csj = j % SCENECHUNK_Y;
			int csk = k % SCENECHUNK_Z;

			// Chunk
			Chunk* c = mChunkArray[Utils::toArrayIndex(ci, cj, ck,
				mCVSize[1], mCVSize[2])];

			return c->getVoxel(csi, csj, csk);
		}
	}

	//---------------------------------------------------------------
	/**
	 * Get chunks
	 */
	vector<Chunk*>* Scene::getChunkArray() {
		return &mChunkArray;
	}
};
