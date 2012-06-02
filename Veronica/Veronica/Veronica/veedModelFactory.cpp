#include "veedModelFactory.h"

// Editor
#include "veedEditor.h"

// Engine
// Ray
#include "veRay.h"
// Renderer
#include "veRenderer.h"


namespace veed {

	/*
	//---------------------------------------------------------------
	ModelFactory::ModelFactory() {

		// Factory operation type
		mOperationType = FOT_NONE;


		// Voxel model
		mModel = NULL;

		// Voxel table serializer
		mSerializer = NULL;


		// Factory history
		mHistory = new FactoryHistory();

		// Current operation snapshot
		mCurrentSnapshot = NULL;


		// Selected voxel group
		mSelectedGroup = "";

		// Mirror flag
		mMirror = false;
	}

	//---------------------------------------------------------------
	ModelFactory::~ModelFactory() {

		// Delete model
		if (mModel) {
			delete mModel;
		}

		// Delete serializer
		if (mSerializer) {
			delete mSerializer;
		}


		// Delete history
		if (mHistory) {
			delete mHistory;
		}
	}


	//---------------------------------------------------------------
	// Init model
	void ModelFactory::initModel() {

		// Create serializer
		mSerializer = new VoxelTableSerializer();


		// Create voxel model
		mModel = new VoxelModel();
		// Load model from file
		mModel->loadFromFile("HeadModel");



		// Create model
		//mModel = new VoxelModel("HeadModel");
		// Create group
		//VoxelGroup* head = new VoxelGroup("Head", 16, 12, 12);
		// Add group to model
		//mModel->addGroup(head->getName(), head);



		// Serialize model
		mModel->serialize(mSerializer);
	}
	*/


	//---------------------------------------------------------------
	/*
	 * Edit model
	 * @param wx {int} x pos relative to window
	 * @param wy {int} y pos relative to window
	 */
	/*
	void ModelFactory::editModel(int wx, int wy) {

		// Do nothing
		if (mOperationType == FOT_NONE) {
			return;
		}


		// Near point in model space
		float np[3];
		if (!Utils::unProject(wx, wy, 0.0f, np)) {
			return;
		}

		// Far point in model space
		float fp[3];
		if (!Utils::unProject(wx, wy, 1.0f, fp)) {
			return;
		}


		// Ray from np to fp in model space
		Ray r = Ray(Vector3(np[0], np[1], np[2]), Vector3(fp[0]-np[0], fp[1]-np[1], fp[2]-np[2]));


		// Test intersection with each group's BB

		// Intersection time
		float min, curNear, curFar;

		// Intersection face
		int fIdx;

		bool first = 1, success = 0;

		// Selected group
		string g = "";


		map<string, VoxelGroup*>::const_iterator group;

		// Loop each group
		for (group = mModel->getGroups().begin(); group != mModel->getGroups().end(); group++) {
		
			// Do intersectino test
			if (rayBoxIntersection(r, group->second->getModelSpaceBB(), curNear, curFar, fIdx)) {

				// Mark success
				success = 1;

				// First time
				if (first) {

					min = curNear;

					g = group->second->getName();

					// Mark first dirty
					first = 0;
				}

				// Compare curNear with min
				if (curNear < min) {

					min = curNear;

					g = group->second->getName();
				}
			}
		}


		// Test succeed
		if (success) {

			// Check whether we select the same group
			if (_checkSelected(g)) {

				// Edit selected group
				_editGroup(r);
			} else {

				// Select group
				_selectGroup(g);
			}
		} else {

			// Debug
			if (VEED_DEBUG) {
				cout<<"[VoxelModelFactory]<<: No group intersected"<<endl;
			}
		}
	}


	//---------------------------------------------------------------
	// Save model to file
	void ModelFactory::saveModel() {

		// Save model to file
		mModel->saveToFile();
	}


	//---------------------------------------------------------------
	// Undo
	void ModelFactory::undo() {

		// Pop undo snapshot from history
		OperationSnapshot* undoSs = mHistory->popUndoSnapshot();

		// No undo snapshot
		if (!undoSs) {
			return;
		}


		// Take current snapshot and restore from old snapshot
		OperationSnapshot* redoSs = _takeSnapshotAndRestore(undoSs);
		
		// Delete undo snapshot
		delete undoSs;


		// Push redo snapshot to history
		mHistory->pushRedoSnapshot(redoSs);
	}

	//---------------------------------------------------------------
	// Redo
	void ModelFactory::redo() {

		// Pop redo snapshot from history
		OperationSnapshot* redoSs = mHistory->popRedoSnapshot();

		// No redo snapshot
		if (!redoSs) {
			return;
		}


		// Take current snapshot and restore fomr old snapshot
		OperationSnapshot* undoSs = _takeSnapshotAndRestore(redoSs);

		// Delete redo snapshot
		delete redoSs;


		// Push undo snapshot to history
		mHistory->pushUndoSnapshot(undoSs);
	}


	//---------------------------------------------------------------
	// Set operation
	void ModelFactory::setOperation(FactoryOperationType t) {
		mOperationType = t;
	}

	//---------------------------------------------------------------
	// Toggle mirror
	void ModelFactory::toggleMirror() {
		mMirror = !mMirror;
	}



	//---------------------------------------------------------------
	// Select group
	void ModelFactory::_selectGroup(const string& groupName) {

		// Set selected group
		mSelectedGroup = groupName;

		// Debug
		if (VEED_DEBUG) {
			cout<<"[VoxelModelFactory]<<: Select group "<<mSelectedGroup<<endl;
		}
	}

	//---------------------------------------------------------------
	// Check selected
	bool ModelFactory::_checkSelected(const string& groupName) {

		return mSelectedGroup == groupName;
	}


	//---------------------------------------------------------------
	// Edit group
	void ModelFactory::_editGroup(Ray& r) {

		// Group
		VoxelGroup* g = mModel->getGroup(mSelectedGroup);


		// Test intersection with each voxel's BB

		// Intersection time
		float min, curNear, curFar;

		// Intersection face
		int fIdx;

		bool first = 1, success = 0;

		// Test result
		int result[4];


		// Voxel table
		VoxelTable* vt = g->getVoxelTable();

		// Voxel table size
		//int x = vt->getSizeX();
		//int y = vt->getSizeY();
		//int z = vt->getSizeZ();
		int x = 0;
		int y = 0;
		int z = 0;


		// Loop each voxel
		for (int i = 0; i < x; i++) {

			for (int j = 0; j < y; j++) {

				for (int k = 0; k < z; k++) {

					// Empty voxel
					if (!vt->getVoxel(i, j, k)) {

						continue;
					}


					// Intersection test with voxel's model space BB
					if (rayBoxIntersection(r, g->getModelSpaceVoxelBB(i, j, k), curNear, curFar, fIdx)) {
					
						// Mark success
						success = 1;


						// First time
						if (first) {

							min = curNear;

							result[0] = i;
							result[1] = j;
							result[2] = k;
							result[3] = fIdx;

							// Mark first dirty
							first = 0;
						}

						// Compare curNear with min
						if (curNear < min) {

							min = curNear;

							result[0] = i;
							result[1] = j;
							result[2] = k;
							result[3] = fIdx;
						}
					}
				}
			}
		}


		// Test succeed
		if (success) {

			// Edit voxels
			_editVoxels(result);

		} else {

			// Debug
			if (VEED_DEBUG) {
				cout<<"[VoxelModelFactory]<<: No voxel intersected"<<endl;
			}
		}
	}


	//---------------------------------------------------------------
	// Edit voxel
	void ModelFactory::_editVoxels(int* selectedVoxelInfo) {

		// Clear redo stack
		mHistory->clearRedo();


		// Create operation snapshot
		mCurrentSnapshot = new OperationSnapshot();


		// Voxel table
		VoxelTable* vt = mModel->getGroup(mSelectedGroup)->getVoxelTable();

		// Voxel table size
		int x = 0; //vt->getSizeX();
		int y = 0; //vt->getSizeY();
		int z = 0; //vt->getSizeZ();


		// Idx
		int i, j, k;

		// Selected voxel
		i = selectedVoxelInfo[0];
		j = selectedVoxelInfo[1];
		k = selectedVoxelInfo[2];

		_takeVoxelSnapshotAndPerformAction(i, j, k);


		if (mMirror) {

			// Mirror voxel
			i = x - selectedVoxelInfo[0] - 1;
			j = selectedVoxelInfo[1];
			k = selectedVoxelInfo[2];

			_takeVoxelSnapshotAndPerformAction(i, j, k);
		}


		// Push current operation snapshot to undo
		mHistory->pushUndoSnapshot(mCurrentSnapshot);

		// Clean current operation snapshot
		mCurrentSnapshot = NULL;
	}


	//---------------------------------------------------------------
	// Take voxel snapshot and perform action
	void ModelFactory::_takeVoxelSnapshotAndPerformAction(int i, int j, int k) {

		// Group
		VoxelGroup* g = mModel->getGroup(mSelectedGroup);

		// Voxel table
		VoxelTable* vt = mModel->getGroup(mSelectedGroup)->getVoxelTable();


		// History
		// Create voxel snapshot
		VoxelSnapshot* vSs = new VoxelSnapshot(mSelectedGroup, i, j, k, vt->getVoxel(i, j, k));

		// Push to current operation snapshot
		mCurrentSnapshot->mList.push_back(vSs);


		// Perform action
		// Delete mode
		if (mOperationType == FOT_DELETE) {

			// Delete voxel
			//vt->setVoxel(i, j, k, NULL);
		}

		// Color mode
		if (mOperationType == FOT_COLOR) {
		
			// Set voxel color
			//vt->setVoxelColor(i, j, k, mColor[0], mColor[1], mColor[2]);
			//vt->setVoxelColor(i, j, k, mEditor->getColorPanelColor()[0]*255, mEditor->getColorPanelColor()[1]*255, mEditor->getColorPanelColor()[2]*255);
		}


		// We need to refresh group's mesh
		g->serialize(mSerializer);
	}


	//---------------------------------------------------------------
	// Take current snapshot and restore from old snapshot
	OperationSnapshot* ModelFactory::_takeSnapshotAndRestore(OperationSnapshot* oldSnapshot) {

		// Current snapshot
		OperationSnapshot* curSnapshot = new OperationSnapshot();


		// Current voxel snapshot
		VoxelSnapshot* curVSs;

		// Old voxel snapshot
		VoxelSnapshot* oldVSs;


		// Group
		VoxelGroup* group;

		// Voxel table
		VoxelTable* vt;

		// Voxel idx
		int i, j, k;


		// Loop each voxel snapshot
		for (uint a = 0; a < oldSnapshot->mList.size(); a++) {

			// Old voxel snapshot
			oldVSs = oldSnapshot->mList.at(a);


			// Group
			group = mModel->getGroup(oldVSs->mGroup);

			// Voxel table
			vt = group->getVoxelTable();

			// Voxel idx
			i = oldVSs->mIdx[0];
			j = oldVSs->mIdx[1];
			k = oldVSs->mIdx[2];


			// Current voxel snapshot
			curVSs = new VoxelSnapshot(oldVSs->mGroup, i, j, k, vt->getVoxel(i, j, k));

			// Push to current snapshot
			curSnapshot->mList.push_back(curVSs);


			// Restore from old voxel snapshot
			//vt->setVoxel(i, j, k, oldVSs->mData ? new Voxel(*(oldVSs->mData)) : NULL);
		}


		// We need to refresh group's mesh
		group->serialize(mSerializer);

		return curSnapshot;
	}
	*/
};