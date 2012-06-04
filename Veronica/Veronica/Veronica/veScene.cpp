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
	 * Test world space coordinate inside or not.
	 */
	bool Scene::testInside(int i, int j, int k) {

		return mVolume.contain(i, j, k);
	}


	//---------------------------------------------------------------
	/**
	 * Convert world space coordinate to chunk local space coordinate.
	 * @i {int} world space x coordinate.
	 * @j {int} world space y coordinate.
	 * @k {int} world space z coordinate.
	 * @cc {int*} result chunk space coordinate: i, j, k, chunkIndex.
	 * @return {bool} succeed or not.
	 */
	bool Scene::worldCoordToChunkCoord(int i, int j, int k, int* cc) {

		if (!testInside(i, j, k)) {

			// Invalid world space coordinate
			return false;
		} else {

			// Chunk coordinate
			int ci = (int)(i / SCENECHUNK_X);
			int cj = (int)(j / SCENECHUNK_Y);
			int ck = (int)(k / SCENECHUNK_Z);

			// Chunk index
			cc[3] = Utils::toArrayIndex(ci, cj, ck, mCVSize[1], mCVSize[2]);

			// Chunk space coordinate
			cc[0] = i % SCENECHUNK_X;
			cc[1] = j % SCENECHUNK_Y;
			cc[2] = k % SCENECHUNK_Z;

			return true;
		}
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

		// Chunk local space coordinate
		int cc[4];

		// Convert world space coordinate to chunk local space coordinate
		if (!worldCoordToChunkCoord(i, j, k, cc)) {
			
			return false;
		} else {

			r = mChunkArray[(uint)cc[3]]->getVoxel(cc[0], cc[1], cc[2]);

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

		// Chunk local space coordinate
		int cc[4];

		// Convert world space coordinate to chunk local space coordinate
		if (!worldCoordToChunkCoord(i, j, k, cc)) {

			return;
		} else {

			mChunkArray[(uint)cc[3]]->setVoxel(cc[0], cc[1], cc[2], v);
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
