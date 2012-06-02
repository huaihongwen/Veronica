#include "veedSceneFactory.h"

namespace veed {

	//---------------------------------------------------------------
	SceneFactory::SceneFactory() {
	}

	//---------------------------------------------------------------
	SceneFactory::~SceneFactory() {
	}

	//---------------------------------------------------------------
	// Init scene
	void SceneFactory::initScene() {

		// Init scene
		mScene.init(32, 16, 16);


		// Set scene to chunk serializer
		mChunkSerializer.setScene(&mScene);

		// Chunk array
		vector<Chunk*>& chunkArray = *mScene.getChunkArray();

		// Loop each chunk
		for (uint i = 0; i < chunkArray.size(); i++) {

			// Serialize chunk
			mSceneMeshesArray.push_back(mChunkSerializer.serialize(chunkArray[i]));
		}


		// Setup renderer's meshes
		Renderer::getSingleton().mTestMeshes = &mSceneMeshesArray;
	}


	//---------------------------------------------------------------
	/**
	 * Handle mouse click
	 * @wx {int} x coordinate relative to window.
	 * @wy {int} y coordinate relative to window.
	 */
	void SceneFactory::handleMouseClick(int wx, int wy) {

		// Near point in world space
		float np[3];
		if (!Utils::unProject(wx, wy, 0.0f, np)) {
			return;
		}

		// Far point in world space
		float fp[3];
		if (!Utils::unProject(wx, wy, 1.0f, fp)) {
			return;
		}

		// Ray from np to fp in world space
		Ray r = Ray(Vector3(np[0], np[1], np[2]), Vector3(fp[0]-np[0], fp[1]-np[1], fp[2]-np[2]));


		// Chunk array
		vector<Chunk*>& chunkArray = *mScene.getChunkArray();

		// Chunk
		Chunk* chunk;


		// Intersection
		// Time
		float min, curNear, curFar;

		// Face index
		int faceIndex;

		// Flag
		bool first = true, succeed = false;

		// Result: (i, j, k, faceIndex, chunkIndex)
		int result[5];


		// BB
		BBox bb;


		// Loop each chunk
		for (uint c = 0; c < chunkArray.size(); c++) {

			// Chunk
			chunk = chunkArray[c];

			// Chunk's volume
			// Position
			int px = chunk->mVolume.mPos[0];
			int py = chunk->mVolume.mPos[1];
			int pz = chunk->mVolume.mPos[2];

			// Size
			int sx = chunk->mVolume.mSize[0];
			int sy = chunk->mVolume.mSize[1];
			int sz = chunk->mVolume.mSize[2];

			// Chunk's world space BB
			bb.setOrigin((float)px, (float)py, (float)pz);
			bb.setSize((float)sx, (float)sy, (float)sz);


			// Do intersection test with chunk's world space BB
			if (rayBoxIntersection(r, bb, curNear, curFar, faceIndex)) {

				// Loop each chunk space coordinate
				for (int i = 0; i < sx; i++) {

					for (int j = 0; j < sy; j++) {

						for (int k = 0; k < sz; k++) {

							if (!chunk->getVoxel(i, j, k)) {

								// Empty voxel
								continue;
							} else {

								// Voxel's world space BB
								bb.setOrigin((float)px+i, (float)py+j, (float)pz+k);
								bb.setSize(1.0f, 1.0f, 1.0f);


								// Do intersection test with voxel's world space BB
								if (rayBoxIntersection(r, bb, curNear, curFar, faceIndex)) {

									// Save or not
									bool save = false;

									// Mark succeed
									succeed = true;


									// First time
									if (first) {

										// Save
										save = true;

										// Mark first dirty
										first = false;

									} else {

										// Compare curNear with min
										if (curNear < min) {

											// Save
											save = true;
										}
									}


									if (save) {

										// Min
										min = curNear;

										// Result
										result[0] = i;
										result[1] = j;
										result[2] = k;
										result[3] = faceIndex;
										result[4] = (int)c;
									}
								}
							}
						}
					}
				}
			}
		}


		// Test succeed
		if (succeed) {
			
			if (VEED_DEBUG) {
				cout<<"[SceneFactory]<<: Intersect with chunk: "<<result[4]<<" voxel: "
					<<result[0]<<" "<<result[1]<<" "<<result[2]<<" face: "<<result[3]<<endl;
			}


			// Edit voxel
			_editVoxel(result);

		} else {

			if (VEED_DEBUG) {
				cout<<"[SceneFactory]<<: No chunk intersected."<<endl;
			}
		}
	}

	//---------------------------------------------------------------
	/**
	 * Edit voxel
	 * @selectedVoxelInfo {int*} selected voxel info (i, j, k, faceIndex, chunkIndex).
	 */
	void SceneFactory::_editVoxel(int* selectedVoxelInfo) {

		// Chunk space coordinate
		int i = selectedVoxelInfo[0];
		int j = selectedVoxelInfo[1];
		int k = selectedVoxelInfo[2];

		// Face index
		int faceIndex = selectedVoxelInfo[3];

		// Chunk index
		uint chunkIndex = selectedVoxelInfo[4];



	}

	//---------------------------------------------------------------
	/**
	 * Refresh mesh
	 * @index {uint} mesh index.
	 */
	void SceneFactory::_refreshMesh(uint index) {

		// Chunk array
		vector<Chunk*>& chunkArray = *mScene.getChunkArray();


		// Delete the old mesh
		delete mSceneMeshesArray[index];

		// Serialize chunk
		mChunkSerializer.serialize(chunkArray[index]);
	}
};