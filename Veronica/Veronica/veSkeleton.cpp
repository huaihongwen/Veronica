#include "veSkeleton.h"


namespace vee {

	//---------------------------------------------------------------
	EditorJoint::EditorJoint() {
	}

	//---------------------------------------------------------------
	EditorJoint::EditorJoint(string& name, EditorJoint* parent) {

		// Name
		mName = name;


		// Parent
		mParent = parent;


		// Local orientation
		mLocalOrientation.setValue(0.0f, 0.0f, 0.0f, 1.0f);

		// Local position
		mLocalPos.setValue(0.0f, 0.0f, 0.0f);
	}

	//---------------------------------------------------------------
	EditorJoint::~EditorJoint() {
	}


	//---------------------------------------------------------------
	// Calculate world orientation and position
	void EditorJoint::worldOrientationAndPos() {

		// No parent
		if (!mParent) {

			mWorldOrientation = mLocalOrientation;

			mWorldPos = mLocalPos;

		} else {

			mWorldOrientation = mParent->mWorldOrientation * mLocalOrientation;

			mWorldPos = Quaternion_rotatePoint(mLocalOrientation, mLocalPos) + mParent->mWorldPos;
		}
	}





	//---------------------------------------------------------------
	EditorSkeleton::EditorSkeleton() {

		// Generated joint number
		mGeneratedJointNum = 0;
	}

	//---------------------------------------------------------------
	EditorSkeleton::~EditorSkeleton() {

		// Loop each joint
		for (uint i = 0; i < mJointArray.size(); i++) {

			// Delete joint
			delete mJointArray[i];
		}
	}


	//---------------------------------------------------------------
	// Init
	void EditorSkeleton::init(string name) {

		// Name
		mName = name;

		// Joint tree
		_createJointFromParent(NULL);


		// FK
		_FK();
	}


	//---------------------------------------------------------------
	// Serialize joint tree into array
	void EditorSkeleton::serialize() {

		// Clear joint array
		mJointArray.clear();


		// Recursively serialize
		_recurSerialize(mJointTree);
	}


	//---------------------------------------------------------------
	// Render
	void EditorSkeleton::render() {

	}



	//---------------------------------------------------------------
	// Recursively serialize
	void EditorSkeleton::_recurSerialize(EditorJoint* joint) {

		// Push to joint array
		mJointArray.push_back(joint);


		// Loop each child
		for (uint i = 0; i < joint->mChildren.size(); i++) {

			_recurSerialize(joint->mChildren[i]);
		}
	}


	//---------------------------------------------------------------
	// Create joint from parent
	void EditorSkeleton::_createJointFromParent(EditorJoint* parent) {

		// Create  .joint
		EditorJoint* joint = new EditorJoint(_generatedJointName(), parent);


		if (parent) {

			// Add joint to parent
			parent->mChildren.push_back(joint);

		} else {

			// Joint is root
			mJointTree = joint;
		}


		// Generated joint number
		mGeneratedJointNum++;


		// Serialize to sync joint tree with joint array
		serialize();
	}


	//---------------------------------------------------------------
	// Generate joint name
	string EditorSkeleton::_generatedJointName() {

		char buffer[16];

		_itoa_s(mGeneratedJointNum, buffer, 10);


		return mName + "_Joint_" + buffer;
	}


	//---------------------------------------------------------------
	// Forward kinematics
	void EditorSkeleton::_FK() {

		// Loop each joint
		for (uint i = 0; i < mJointArray.size(); i++) {

			// Calculate world orientation and position
			mJointArray[i]->worldOrientationAndPos();
		}
	}
};

