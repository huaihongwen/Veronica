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

	// Voxel snapshot
	typedef struct VoxelSnapshot {

		// Group name
		string mGroup;

		// Idx
		int mIdx[3];

		// Copied voxel data
		Voxel* mData;


		//---------------------------------------------------------------
		VoxelSnapshot() {
		}

		//---------------------------------------------------------------
		VoxelSnapshot(const string& group, int i, int j, int k, Voxel* data) {
		
			// Group name
			mGroup = group;

			// Idx
			mIdx[0] = i;
			mIdx[1] = j;
			mIdx[2] = k;

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


	// Operation snapshot
	typedef struct OperationSnapshot {

		// VoxelSnapshot list
		vector<VoxelSnapshot*> mList;

		//---------------------------------------------------------------
		OperationSnapshot() {
		}

		//---------------------------------------------------------------
		~OperationSnapshot() {

			// Clear all VoxelSnapshot
			for (uint i = 0; i < mList.size(); i++) {

				// Delete VoxelSnapshot
				delete mList.at(i);
			}
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
		// Max operation snapshot number
		uint mMaxNum;


		// Undo stack
		deque<OperationSnapshot*> mUndoStack;

		// Redo stack
		deque<OperationSnapshot*> mRedoStack;
	};
};

#endif