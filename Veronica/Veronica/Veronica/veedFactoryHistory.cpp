#include "veedFactoryHistory.h"


namespace veed {

	//---------------------------------------------------------------
	FactoryHistory::FactoryHistory(uint num) {

		// Max operation snapshot number
		mMaxNum = num;
	}

	//---------------------------------------------------------------
	FactoryHistory::~FactoryHistory() {

		// Clear undo stack
		clearUndo();

		// Clear redo stack
		clearRedo();
	}


	//---------------------------------------------------------------
	// Clear undo stack
	void FactoryHistory::clearUndo() {

		// Loop each operation snapshot
		for (uint i = 0; i < mUndoStack.size(); i++) {

			// Delete operation snapshot
			delete mUndoStack.at(i);
		}

		// Clear
		mUndoStack.clear();
	}

	//---------------------------------------------------------------
	// Clear redo stack
	void FactoryHistory::clearRedo() {

		// Loop each operation snapshot
		for (uint i = 0; i < mRedoStack.size(); i++) {

			// Delete operation snapshot
			delete mRedoStack.at(i);
		}

		// Clear
		mRedoStack.clear();
	}


	//---------------------------------------------------------------
	// Push undo snapshot
	void FactoryHistory::pushUndoSnapshot(OperationSnapshot* ss) {

		// Reach max number
		if (mUndoStack.size() == mMaxNum) {

			// Delete oldest snapshot
			delete mUndoStack.at(0);

			mUndoStack.pop_front();
		}


		// Push snapshot to undo stack
		mUndoStack.push_back(ss);


		// Debug
		if (VEED_DEBUG) {
			cout<<"[FactoryHistory]<<: Push undo snapshot, Undo size: "<<mUndoStack.size()<<endl;
		}
	}
	
	//---------------------------------------------------------------
	// Push redo snapshot
	void FactoryHistory::pushRedoSnapshot(OperationSnapshot* ss) {

		// Push snapshot to redo stack
		mRedoStack.push_back(ss);


		// Debug
		if (VEED_DEBUG) {
			cout<<"[FactoryHistory]<<: Push redo snapshot, Redo size: "<<mRedoStack.size()<<endl;
		}
	}


	//---------------------------------------------------------------
	// Pop undo snapshot
	OperationSnapshot* FactoryHistory::popUndoSnapshot() {

		// Size
		uint size = mUndoStack.size();

		// Empty undo stack
		if (!size) {
			return NULL;
		}


		// Operation snapshot
		OperationSnapshot* ss = mUndoStack.at(size-1);

		// Pop snapshot
		mUndoStack.pop_back();


		// Debug
		if (VEED_DEBUG) {
			cout<<"[FactoryHistory]<<: Pop undo snapshot, Undo size: "<<mUndoStack.size()<<endl;
		}


		return ss;
	}

	//---------------------------------------------------------------
	// Pop redo snapshot
	OperationSnapshot* FactoryHistory::popRedoSnapshot() {

		// Size
		uint size = mRedoStack.size();

		// Empty redo stack
		if (!size) {
			return NULL;
		}

		// Operation snapshot
		OperationSnapshot* ss = mRedoStack.at(size-1);

		// Pop snapshot
		mRedoStack.pop_back();


		// Debug
		if (VEED_DEBUG) {
			cout<<"[FactoryHistory]<<: Pop redo snapshot, Redo size: "<<mRedoStack.size()<<endl;
		}


		return ss;
	}
};