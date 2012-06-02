#ifndef VEED_MODELFACTORY_H
#define VEED_MODELFACTORY_H

/*
 * veedModelFactory.h
 */

#include "veedPrerequisites.h"
// Factory history
//#include "veedFactoryHistory.h"


// Engine
// Voxel model
#include "veVoxelModel.h"

namespace veed {

	/*
	// Model factory operation type
	typedef enum FactoryOperationType {
	
		// None
		FOT_NONE,

		// Delete
		FOT_DELETE,

		// Color
		FOT_COLOR

	} FactoryOperationType;




	// Model factory
	class ModelFactory {

	public:
		ModelFactory();
		~ModelFactory();


	public:
		// Init model
		void initModel();

		// Edit model
		void editModel(int wx, int wy);

		// Save model to file
		void saveModel();


		// History
		// Undo
		void undo();

		// Redo
		void redo();


	public:
		// Set operation
		void setOperation(FactoryOperationType t);

		// Toggle mirror
		void toggleMirror();


	protected:
		// Select group
		void _selectGroup(const string& groupName);

		// Check selected
		bool _checkSelected(const string& groupName);


		// Edit group
		void _editGroup(Ray& r);


		// Edit voxels
		void _editVoxels(int* selectedVoxelInfo);


		// History
		// Take voxel snapshot and perform action
		void _takeVoxelSnapshotAndPerformAction(int i, int j, int k);

		// Take current snapshot and restore from old snapshot
		OperationSnapshot* _takeSnapshotAndRestore(OperationSnapshot* oldSnapshot);

	
	protected:
		// Factory operation type
		FactoryOperationType mOperationType;


		// Voxel model
		VoxelModel* mModel;

		// Voxel table serializer
		VoxelTableSerializer* mSerializer;


		// Factory history
		FactoryHistory* mHistory;

		// Current operation snapshot
		OperationSnapshot* mCurrentSnapshot;


		// Selected voxel group
		string mSelectedGroup;

		// Mirror flag
		bool mMirror;

		// Edit color
		uchar mColor[3];


	public:
		Editor* mEditor;
	};
	*/
};

#endif