#include "veedSceneFactory.h"

namespace veed {

	//---------------------------------------------------------------
	SceneFactory::SceneFactory() {

		// Scene factory mode
		mMode = SFM_REMOVE;
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

		// Result: world space i, j, k, faceIndex
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
										result[0] = px + i;
										result[1] = py + j;
										result[2] = pz + k;
										result[3] = faceIndex;
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
			
			//if (VEED_DEBUG) {
			//	cout<<"[SceneFactory]<<: Intersect with: "<<" voxel: "
			//		<<result[0]<<" "<<result[1]<<" "<<result[2]<<" face: "<<result[3]<<endl;
			//}


			// Edit voxel
			_editVoxel(result);

		} else {

			//if (VEED_DEBUG) {
			//	cout<<"[SceneFactory]<<: No voxel intersected."<<endl;
			//}
		}
	}


	//---------------------------------------------------------------
	/**
	 * Handle key pressed
	 * @key {WPARAM} input key.
	 */
	void SceneFactory::handleKeyPressed(WPARAM key) {

		switch (key) {

		// Undo
		case 'z':
			_undo();
			break;

		// Redo
		case 'y':
			_redo();
			break;

		default:
			break;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Edit voxel
	 * @iInfo {int*} intersection voxel info: world space i, j, k, faceIndex.
	 */
	void SceneFactory::_editVoxel(int* iInfo) {

		// Target voxel info
		int tInfo[3];
		_targetVoxelInfo(iInfo, tInfo);

		// Target voxel
		Voxel* v = NULL;


		// Try to get target voxel
		if (!mScene.getVoxel(tInfo[0], tInfo[1], tInfo[2], v)) {

			// Invalid target voxel
			return;
		}


		// Handle history
		// Clear redo
		mHistory.clearRedo();

		// Current OperationSnapshot
		OperationSnapshot* os = new OperationSnapshot();

		// Push VoxelSnaphot
		os->mVSArray.push_back(new VoxelSnapshot(tInfo[0], tInfo[1], tInfo[2], v));

		// Push OperationSnapshot to undo stack
		mHistory.pushUndoSnapshot(os);


		// Perform action
		// Mode
		switch (mMode) {

		// Remove voxel
		case SFM_REMOVE:
			mScene.setVoxel(tInfo[0], tInfo[1], tInfo[2], NULL);
			break;

		// Add voxel
		case SFM_ADD:
			mScene.setVoxel(tInfo[0], tInfo[1], tInfo[2], new Voxel());
			break;

		default:
			break;
		}


		// Refresh meshes
		_refreshMeshes(tInfo[0], tInfo[1], tInfo[2]);
	}


	//---------------------------------------------------------------
	/**
	 * Target voxel info
	 * Base on intersection voxel info and mode, find out target voxel info.
	 * @iInfo {int*} intersection voxel info: i, j, k, faceIndex.
	 * @tInfo {int*} target voxel info: i, j, k.
	 */
	void SceneFactory::_targetVoxelInfo(int* iInfo, int* tInfo) {

		// Target voxel info
		tInfo[0] = iInfo[0];
		tInfo[1] = iInfo[1];
		tInfo[2] = iInfo[2];

		// Mode
		if (mMode == SFM_ADD) {

			// Face index
			switch (iInfo[3]) {

			case 0:
				tInfo[0] -= 1;
				break;

			case 1:
				tInfo[0] += 1;
				break;

			case 2:
				tInfo[1] -= 1;
				break;

			case 3:
				tInfo[1] += 1;
				break;

			case 4:
				tInfo[2] -= 1;
				break;

			case 5:
				tInfo[2] += 1;
				break;

			default:
				return;
			}			
		}
	}

	//---------------------------------------------------------------
	/**
	 * Refresh mesh
	 * @i {int} world space x coordinate.
	 * @j {int} world space y coordinate.
	 * @k {int} world space z coordinate.
	 */
	void SceneFactory::_refreshMeshes(int i, int j, int k) {

		// Chunk coordinate
		int cc[4];

		// Neighbor chunk coordinate
		int ncc[4];


		// Chunk coordinate
		mScene.worldCoordToChunkCoord(i, j, k, cc);

		// Refresh chunk mesh
		_refreshChunkMesh((uint)cc[3]);


		// Check 6 neighbors

		// -x
		if (mScene.worldCoordToChunkCoord(i-1, j, k, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}

		// -x
		if (mScene.worldCoordToChunkCoord(i+1, j, k, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}

		// -y
		if (mScene.worldCoordToChunkCoord(i, j-1, k, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}

		// y
		if (mScene.worldCoordToChunkCoord(i, j+1, k, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}

		// -z
		if (mScene.worldCoordToChunkCoord(i, j, k-1, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}

		// z
		if (mScene.worldCoordToChunkCoord(i, j, k+1, ncc) && (cc[3] != ncc[3])) {
			// Refresh neighbor
			_refreshChunkMesh((uint)ncc[3]);
		}
	}

	//---------------------------------------------------------------
	/**
	 * Refresh chunk mesh
	 */
	void SceneFactory::_refreshChunkMesh(uint i) {

		// Delete old mesh
		delete mSceneMeshesArray[i];

		// Refresh chunk mesh
		mSceneMeshesArray[i] = mChunkSerializer.serialize((*mScene.getChunkArray())[i]);
	}


	//---------------------------------------------------------------
	/**
	 * Undo
	 */
	void SceneFactory::_undo() {

		
		// Pop undo OperationSnapshot from history
		OperationSnapshot* undoOS = mHistory.popUndoSnapshot();

		// No undo OperationSnapshot
		if (!undoOS) {
			return;
		}

		// Take current OperationSnapshot and restore from old OperationSnapshot
		OperationSnapshot* redoOS = _restore(undoOS);

		// Delete undo OperationSnapshot
		delete undoOS;

		// Push redo OperationSnapshot to history
		mHistory.pushRedoSnapshot(redoOS);
		
	}

	//---------------------------------------------------------------
	/**
	 * Redo
	 */
	void SceneFactory::_redo() {

		// Pop redo OperationSnapshot from history
		OperationSnapshot* redoOS = mHistory.popRedoSnapshot();

		// No redo OperationSnapshot
		if (!redoOS) {
			return;
		}

		// Take current OperationSnapshot and restore from old OperationSnapshot
		OperationSnapshot* undoOS = _restore(redoOS);

		// Delete redo OperationSnapshot
		delete redoOS;

		// Push undo OperationSnapshot to history
		mHistory.pushUndoSnapshot(undoOS);
	}

	//---------------------------------------------------------------
	/**
	 * Restore
	 * Create current OperationSnapshot and restore from old OperationSnapshot.
	 * @oldOS {OperationSnapshot*} old OperationSnapshot.
	 * @return {OperationSnapshot*} current OperationSnapshot.
	 */
	OperationSnapshot* SceneFactory::_restore(OperationSnapshot* oldOS) {

		// Old VoxelSnapshot
		VoxelSnapshot* oldVS;

		// Current OperationSnapshot
		OperationSnapshot* curOS = new OperationSnapshot();

		// Current VoxelSnapshot
		VoxelSnapshot* curVS;


		// World space coordinate
		int i, j, k;

		// Old voxel data
		Voxel* oldData;

		// Current voxel data
		Voxel* curData;


		// Loop each old VoxelSnapshot
		for (uint a = 0; a < oldOS->mVSArray.size(); a++) {
		
			// Old VoxelSnapshot
			oldVS = oldOS->mVSArray[a];

			// World space coordinate
			i = oldVS->mCoord[0];
			j = oldVS->mCoord[1];
			k = oldVS->mCoord[2];

			// Old voxel data
			oldData = oldVS->mData;


			// Current voxel data
			mScene.getVoxel(i, j, k, curData);

			// Current VoxelSnapshot
			curVS = new VoxelSnapshot(i, j, k, curData);

			// Push current VoxelSnapshot to current OperationSnapshot
			curOS->mVSArray.push_back(curVS);


			// Perform action
			// Set voxel
			mScene.setVoxel(i, j, k, oldData ? new Voxel(*oldData) : NULL);

			// Refresh mesh
			_refreshMeshes(i, j, k);
		}


		return curOS;
	}

};