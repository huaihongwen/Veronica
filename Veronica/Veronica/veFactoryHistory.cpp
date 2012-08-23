#include "veFactoryHistory.h"

namespace vee {

	//---------------------------------------------------------------
	FactoryHistory::FactoryHistory(uint num) {

		// Max OperationSnapshot number
		mMaxNum = num;
	}

	//---------------------------------------------------------------
	FactoryHistory::~FactoryHistory() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void FactoryHistory::init() {

	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void FactoryHistory::destroy() {

		// Clear undo stack
		clearUndo();

		// Clear redo stack
		clearRedo();
	}


	//---------------------------------------------------------------
	// Clear undo stack
	void FactoryHistory::clearUndo() {

		// Loop each OperationSnapshot
		for (uint i = 0; i < mUndoStack.size(); i++) {

			// Delete OperationSnapshot
			delete mUndoStack.at(i);
		}

		// Clear
		mUndoStack.clear();
	}

	//---------------------------------------------------------------
	// Clear redo stack
	void FactoryHistory::clearRedo() {

		// Loop each OperationSnapshot
		for (uint i = 0; i < mRedoStack.size(); i++) {

			// Delete OperationSnapshot
			delete mRedoStack.at(i);
		}

		// Clear
		mRedoStack.clear();
	}


	//---------------------------------------------------------------
	// Push undo snapshot
	void FactoryHistory::pushUndoSnapshot(OperationSnapshot* os) {

		// Reach max number
		if (mUndoStack.size() == mMaxNum) {

			// Delete oldest snapshot
			delete mUndoStack[0];

			mUndoStack.pop_front();
		}


		// Push snapshot to undo stack
		mUndoStack.push_back(os);


		// Debug
		if (DEBUGMODE) {
			cout<<"[FactoryHistory]<<: Push undo snapshot, Undo size: "<<mUndoStack.size()<<endl;
		}
	}
	
	//---------------------------------------------------------------
	// Push redo snapshot
	void FactoryHistory::pushRedoSnapshot(OperationSnapshot* os) {

		// Push snapshot to redo stack
		mRedoStack.push_back(os);


		// Debug
		if (DEBUGMODE) {
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
		OperationSnapshot* os = mUndoStack[size-1];

		// Pop snapshot
		mUndoStack.pop_back();


		// Debug
		if (DEBUGMODE) {
			cout<<"[FactoryHistory]<<: Pop undo snapshot, Undo size: "<<mUndoStack.size()<<endl;
		}


		return os;
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
		OperationSnapshot* os = mRedoStack[size-1];

		// Pop snapshot
		mRedoStack.pop_back();


		// Debug
		if (DEBUGMODE) {
			cout<<"[FactoryHistory]<<: Pop redo snapshot, Redo size: "<<mRedoStack.size()<<endl;
		}


		return os;
	}
};