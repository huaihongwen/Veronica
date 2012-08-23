#include "veSceneFactory.h"
#include "veEditor.h"


namespace vee {

	//---------------------------------------------------------------
	SceneFactory::SceneFactory() {
	}

	//---------------------------------------------------------------
	SceneFactory::~SceneFactory() {

		// Destroy
		destroy();
	}

	//---------------------------------------------------------------
	/**
	 * Clean
	 * Clean attributes with default value.
	 */
	void SceneFactory::_clean() {

		// Input data
		// Chunk
		_mChunk = NULL;

		// Chunk mesh
		_mMesh = NULL;

		// Factory history
		_mHistory = NULL;


		// Edit related data
		// Current OperationSnapshot
		_mOpSsCur = NULL;

		// Chunk copy
		_mChunkCopy = NULL;


		// Params
		// Scene factory mode
		_mMode = SFM_REMOVE;

		// Current voxel color
		_mVoxelColorCur[0] = 255;
		_mVoxelColorCur[1] = 255;
		_mVoxelColorCur[2] = 255;

		// Current voxel type
		_mVoxelTypeCur = VT_DEFAULT;


		// Intersection flag
		_mIstFlag = false;

		// Operation flag
		_mOpFlag = false;


		// Events
		// Color panel event handler id
		_mColorPanelEventHandlerId = -1;
	}


	//--------------------------------------------------------------
	/**
	 * Init
	 * @c {Chunk*} input chunk.
	 * @m {Mesh*} input mesh.
	 * @h {FactoryHistory*} input history.
	 */
	void SceneFactory::init(Chunk* c, Mesh* m, FactoryHistory* h) {

		// Clean
		_clean();


		// Input data
		// Chunk
		_mChunk = c;

		// Chunk mesh
		_mMesh = m;

		// Factory history
		_mHistory = h;


		// Bind events
		_bindEvents();


		// Serialize chunk mesh
		mSerializer.serialize(_mChunk, _mMesh);


		// Renderer
		Renderer& r = Renderer::getSingleton();
		// Set mesh to renderer
		r.mTestMesh = _mMesh;
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void SceneFactory::destroy() {

		// Unbind events
		_unbindEvents();


		// Current OperationSnapshot
		if (_mOpSsCur) {
			delete _mOpSsCur;
		}

		// Chunk copy
		if (_mChunkCopy) {
			delete _mChunkCopy;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Bind events
	 */
	void SceneFactory::_bindEvents() {

		// Attach to color panel select event
		//mColorSelectionEvtHandlerId = mParent->mColorSelection->mEvent.attach(this,
			//&vee::SceneFactory::_onColorPanelSelect);

		// Attach to texture panel select event
		//mTexturePanelEventHandlerId = mParent->mUITexturePanel->mEvent.attach(this,
			//&vee::SceneFactory::_onTexturePanelSelect);
	}

	//---------------------------------------------------------------
	/**
	 * Unbind events
	 */
	void SceneFactory::_unbindEvents() {

		// Detach from texture panel select event
		//mParent->mUITexturePanel->mEvent.detach(mTexturePanelEventHandlerId);
	}

	//---------------------------------------------------------------
	/**
	 * On color panel select
	 */
	bool SceneFactory::_onColorPanelSelect(float* c) {

		// Current voxel color
		_mVoxelColorCur[0] = uchar(255 * c[0]);
		_mVoxelColorCur[1] = uchar(255 * c[1]);
		_mVoxelColorCur[2] = uchar(255 * c[2]);

		// Current voxel type
		_mVoxelTypeCur = VT_DEFAULT;

		return true;
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button down
	 * @wx {int} x coordinate relative to window.
	 * @wy {int} y coordinate relative to window.
	 */
	void SceneFactory::mouseLDown(int x, int y) {

		// If we already intersected with chunk
		if (_mIstFlag) {

			// Start an operation
			_mOpFlag = true;


			// Intersection data
			// Setup intersection "from"
			memcpy(_mIstFrom, _mIstCur, 16);
			// Setup intersection "to"
			memcpy(_mIstTo, _mIstCur, 16);


			// Current OperationSnapshot
			_mOpSsCur = new OperationSnapshot();

			// Chunk copy
			_mChunkCopy = new Chunk();
			_mChunkCopy->init(_mChunk);


			// Process operation volume on chunk copy
			_processOperationVolume();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 * @wx {int} x coordinate relative to window.
	 * @wy {int} y coordinate relative to window.
	 */
	void SceneFactory::mouseLUp(int x, int y) {

		// If we already started an operation
		if (_mOpFlag) {

			// End the operation
			_mOpFlag = false;


			// Take OperationSnapshot from chunk copy
			OperationSnapshot* op = _takeOpSs(_mChunkCopy, _mOpSsCur);

			// Apply OperationSnapshot to chunk,
			// this would sync chunk and chunk copy
			_applyOpSs(_mChunk, op);

			// Delte OperationSnapshot
			delete op;


			// Delete chunk copy
			delete _mChunkCopy;

			// Null chunk copy
			_mChunkCopy = NULL;


			// History
			// Clear redo
			_mHistory->clearRedo();

			// Push current OperationSnapshot to undo
			_mHistory->pushUndoSnapshot(_mOpSsCur);

			// Null current OpertionSnapshot
			_mOpSsCur = NULL;
		}
	}

	//---------------------------------------------------------------
	// TODO: Use timer or counter to reduce the intersection frequency.
	/**
	 * Mouse move
	 * @x {int} x coordinate after moved.
	 * @y {int} y coordinate after moved.
	 */
	void SceneFactory::mouseMove(int x, int y) {

		// Intersection test
		_mIstFlag = _intersectionTest(x, y, _mIstCur);


		// If we already started an operation
		if (_mOpFlag) {

			// If current intersection do not equal to intersection "to"
			if (memcmp(_mIstCur, _mIstTo, 16)) {

				// Setup intersection "to"
				memcpy(_mIstTo, _mIstCur, 16);


				// Process operation volume
				_processOperationVolume();
			}
		}


		// Tell renderer to render indicator
		// Renderer
		Renderer& r = Renderer::getSingleton();


		// If we already started an operation
		if (_mOpFlag) {

			// Indicator visible
			r.mIndicatorVisible = true;

			// Render intersection "to"
			memcpy(r.mIndicatorPos, _mIstTo, 16);
		} else {

			// If we already intersected with chunk
			if (_mIstFlag) {

				// Indicator visible
				r.mIndicatorVisible = true;

				// Render current intersection
				memcpy(r.mIndicatorPos, _mIstCur, 16);
			} else {

				// Indicator invisible
				r.mIndicatorVisible = false;
			}
		}
	}


	//---------------------------------------------------------------
	/**
	 * Key pressed
	 * @key {WPARAM} input key.
	 */
	void SceneFactory::keyPressed(WPARAM key) {

		switch (key) {

		// Undo
		case 'z':
			{
				// Undo
				_undo();
			}
			break;

		// Redo
		case 'y':
			{
				// Redo
				_redo();
			}
			break;

		// Remove mode
		case '1':
			_mMode = SFM_REMOVE;
			break;

		// Add mode
		case '2':
			break;

		// Edit mode
		case '3':
			break;

		default:
			break;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Intersection test
	 * If the test result is true, this function would save the nearest intersection
	 * info in result array, if not, the original value in result array would not change.
	 *
	 * @x {int} x coordinate relative to window upper left corner.
	 * @y {int} y coordinate relative to window upper left corner.
	 * @result {int*} result pointer.
	 * @return {bool} intersection succeed or not.
	 */
	bool SceneFactory::_intersectionTest(int x, int y, int* result) {

		// Near point in world space
		float np[3];
		if (!Utils::unProject(x, y, 0.0f, np)) {
			return false;
		}

		// Far point in world space
		float fp[3];
		if (!Utils::unProject(x, y, 1.0f, fp)) {
			return false;
		}

		// Ray from np to fp in world space
		Ray r;
		r.setOrigin(np[0], np[1], np[2]);
		r.setDirection(fp[0]-np[0], fp[1]-np[1], fp[2]-np[2]);


		// Intersection
		// Time
		float min, curNear, curFar;

		// Face index
		int faceIndex;

		// Flag
		bool first = true, succeed = false;


		// BB
		BBox bb;


		// Voxel
		Voxel* v;


		// Chunk's volume
		// Position
		int px = _mChunk->mVolume.mPos[0];
		int py = _mChunk->mVolume.mPos[1];
		int pz = _mChunk->mVolume.mPos[2];

		// Size
		int sx = _mChunk->mVolume.mSize[0];
		int sy = _mChunk->mVolume.mSize[1];
		int sz = _mChunk->mVolume.mSize[2];


		// Loop each chunk space coordinate
		for (int i = 0; i < sx; i++) {

			for (int j = 0; j < sy; j++) {

				for (int k = 0; k < sz; k++) {

					if (!_mChunk->getVoxel(i, j, k, v) || !v) {

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
							}
						}
					}
				}
			}
		}

		return succeed;
	}


	//---------------------------------------------------------------
	/**
	 * Process chunk copy with new operation volume
	 */
	void SceneFactory::_processOperationVolume() {

		// Apply current OperationSnapshot to chunk copy,
		// This would sync chunk and chunk copy
		_applyOpSs(_mChunkCopy, _mOpSsCur);

		// Clean current OperationSnapshot
		_mOpSsCur->destroy();


		// Process new operation volume
		// Operation volume size
		int sx = abs(_mIstFrom[0] - _mIstTo[0]) + 1;
		int sy = abs(_mIstFrom[1] - _mIstTo[1]) + 1;
		int sz = abs(_mIstFrom[2] - _mIstTo[2]) + 1;

		// Operation volume pos
		int px = (_mIstFrom[0] <= _mIstTo[0]) ? _mIstFrom[0] : _mIstTo[0];
		int py = (_mIstFrom[1] <= _mIstTo[1]) ? _mIstFrom[1] : _mIstTo[1];
		int pz = (_mIstFrom[2] <= _mIstTo[2]) ? _mIstFrom[2] : _mIstTo[2];


		// Chunk space coordinates
		int cc[3];

		// Chunk voxel
		Voxel* v;


		// Loop each voxel
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					// Chunk space coordinates
					cc[0] = px + i;
					cc[1] = py + j;
					cc[2] = pz + k;

					// Chunk voxel
					_mChunk->getVoxel(cc[0], cc[1], cc[2], v);


					// Current OperationSnapshot
					_mOpSsCur->mVSArray.push_back(new VoxelSnapshot(cc[0], cc[1], cc[2], v));


					// Process voxel
					switch (_mMode) {

						// Remove voxel
					case SFM_REMOVE:
						_mChunkCopy->setVoxel(cc[0], cc[1], cc[2], NULL);
						break;

					default:
						break;
					}
				}
			}
		}


		// Serialize mesh
		mSerializer.serialize(_mChunkCopy, _mMesh);
	}


	//---------------------------------------------------------------
	/**
	 * Apply OperationSnapshot
	 * Modify chunk with OperationSnapshot, this would not modify OperationSnapshot
	 *
	 * @c {Chunk*} chunk.
	 * @opSs {OperationSnapshot*} OperationSnapshot.
	 */
	void SceneFactory::_applyOpSs(Chunk* c, OperationSnapshot* opSs) {

		// VoxelSnapshot
		VoxelSnapshot* vSs;

		// Voxel
		Voxel* v;


		// Loop each VoxelSnapshot
		for (uint i = 0; i < opSs->mVSArray.size(); i++) {

			// VoxelSnapshot
			vSs = opSs->mVSArray[i];

			// Copy voxel data
			v = vSs->mData ? new Voxel(*vSs->mData) : NULL;


			// Set voxel
			c->setVoxel(vSs->mCoord[0], vSs->mCoord[1], vSs->mCoord[2], v);
		}
	}

	//---------------------------------------------------------------
	/**
	 * Take OperationSnapshot
	 * Take OperationSnapshot with reference OperationSnapshot, this would not modify chunk
	 * and reference OperationSnapshot.
	 *
	 * @c {Chunk*} chunk.
	 * @refOpSs {OperationSnapshot*} reference OperationSnapshot.
	 * @return {OperationSnapshot*} result OperationSnapshot.
	 */
	OperationSnapshot* SceneFactory::_takeOpSs(Chunk* c, OperationSnapshot* refOpSs) {

		// Reference VoxelSnapshot
		VoxelSnapshot* refVSs;


		// Chunk voxel
		Voxel* v;

		// Chunk space coordinates
		int cc[3];


		// Result OperationSnapshot
		OperationSnapshot* resultOpSs = new OperationSnapshot();


		// Loop each renference VoxelSnapshot
		for (uint i = 0; i < refOpSs->mVSArray.size(); i++) {

			// Reference VoxelSnapshot
			refVSs = refOpSs->mVSArray[i];


			// Chunk space coordinates
			cc[0] = refVSs->mCoord[0];
			cc[1] = refVSs->mCoord[1];
			cc[2] = refVSs->mCoord[2];

			// Chunk voxel
			c->getVoxel(cc[0], cc[1], cc[2], v);


			// Result VoxelSnapshot
			resultOpSs->mVSArray.push_back(new VoxelSnapshot(cc[0], cc[1], cc[2], v));
		}


		return resultOpSs;
	}


	//---------------------------------------------------------------
	/**
	 * Undo
	 */
	void SceneFactory::_undo() {

		// Pop undo OperationSnapshot
		OperationSnapshot* undo = _mHistory->popUndoSnapshot();

		// No undo OperationSnapshot
		if (!undo) {
			return;
		}


		// Take redo OperationSnapshot
		OperationSnapshot* redo = _takeOpSs(_mChunk, undo);


		// Apply undo OperationSnapshot
		_applyOpSs(_mChunk, undo);

		// Delete undo OperationSnapshot
		delete undo;


		// Push redo OperationSnapshot
		_mHistory->pushRedoSnapshot(redo);


		// Serialize mesh
		mSerializer.serialize(_mChunk, _mMesh);
	}

	//---------------------------------------------------------------
	/**
	 * Redo
	 */
	void SceneFactory::_redo() {

		// Pop redo OperationSnapshot
		OperationSnapshot* redo = _mHistory->popRedoSnapshot();

		// No redo OperationSnapshot
		if (!redo) {
			return;
		}


		// Take undo OperationSnapshot
		OperationSnapshot* undo = _takeOpSs(_mChunk, redo);


		// Apply redo OperationSnapshot
		_applyOpSs(_mChunk, redo);

		// Delete redo OperationSnapshot
		delete redo;

		// Push undo OperationSnapshot
		_mHistory->pushUndoSnapshot(undo);


		// Serialize mesh
		mSerializer.serialize(_mChunk, _mMesh);
	}
};