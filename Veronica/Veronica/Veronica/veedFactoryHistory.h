#ifndef VEED_FACTORYHISTORY_H
#define VEED_FACTORYHISTORY_H


/*
 * veedFactoryHistory.h
 */


#include "veedPrerequisites.h"

// Engine
#include "veVoxel.h"

#include <vector>
#include <deque>


namespace veed {

	/**
	 * Voxel snapshot
	 */
	typedef struct VoxelSnapshot {

		// World space coordinate
		int mCoord[3];

		// Copied voxel data
		Voxel* mData;


		//---------------------------------------------------------------
		VoxelSnapshot() {
		}

		//---------------------------------------------------------------
		VoxelSnapshot(int i, int j, int k, Voxel* data) {

			// World space coordinate
			mCoord[0] = i;
			mCoord[1] = j;
			mCoord[2] = k;

			// Copied voxel data
			if (data) {
				mData = new Voxel(*data);
			} else {
				mData = NULL;
			}
		}

		//---------------------------------------------------------------
		~VoxelSnapshot() {

			// Delete copied voxel data
			if (mData) {
				delete mData;
			}
		}

	} VoxelSnapshot;


	/**
	 * Operation snapshot
	 */
	typedef struct OperationSnapshot {

		// VoxelSnapshot array
		vector<VoxelSnapshot*> mVSArray;

		//---------------------------------------------------------------
		OperationSnapshot() {
		}

		//---------------------------------------------------------------
		~OperationSnapshot() {

			// Loop each VoxelSnapshot
			for (uint i = 0; i < mVSArray.size(); i++) {

				// Delete VoxelSnapshot
				delete mVSArray[i];
			}

			// Clear
			mVSArray.clear();
		}
	} OperationSnapshot;



	// Factory history
	class FactoryHistory {

	public:
		FactoryHistory(uint num=50);
		~FactoryHistory();


	public:
		// Clear undo stack
		void clearUndo();

		// Clear redo stack
		void clearRedo();


		// Push undo snapshot
		void pushUndoSnapshot(OperationSnapshot* ss);

		// Push redo snapshot
		void pushRedoSnapshot(OperationSnapshot* ss);


		// Pop undo snapshot
		OperationSnapshot* popUndoSnapshot();

		// Pop redo snapshot
		OperationSnapshot* popRedoSnapshot();


	protected:
		// Max OperationSnapshot number
		uint mMaxNum;


		// Undo stack
		deque<OperationSnapshot*> mUndoStack;

		// Redo stack
		deque<OperationSnapshot*> mRedoStack;
	};
};

#endif