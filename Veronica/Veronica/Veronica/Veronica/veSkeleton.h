#ifndef VEE_SKELETON_H
#define VEE_SKELETON_H


/*
 * veSkeleton.h
 */


#include "vePrerequisites.h"
#include "veQuaternion.h"

#include <vector>


namespace vee {

	// Editor joint
	typedef struct EditorJoint {

		// Name
		string mName;


		// Parent
		EditorJoint* mParent;

		// Children
		vector<EditorJoint*> mChildren;


		// Local orientation
		Quaternion mLocalOrientation;

		// Local position
		Vector3 mLocalPos;


		// World orientation
		Quaternion mWorldOrientation;

		// World position
		Vector3 mWorldPos;



		//---------------------------------------------------------------
		EditorJoint();
		EditorJoint(string& name, EditorJoint* parent);
		~EditorJoint();


		// Calculate world orientation and position
		void worldOrientationAndPos();

	} EditorJoint;





	// Editor skeleton
	typedef struct EditorSkeleton {

		// Name
		string mName;


		// Joint tree
		EditorJoint* mJointTree;

		// Joint array
		vector<EditorJoint*> mJointArray;


		// Generated joint number
		int mGeneratedJointNum;



		//---------------------------------------------------------------
		EditorSkeleton();
		~EditorSkeleton();


		// Init
		void init(string name);


		// Serialize joint tree into array
		void serialize();


		// Render
		void render();


		//---------------------------------------------------------------
		// Recursively serialize
		void _recurSerialize(EditorJoint* joint);


		// Create joint from parent
		void _createJointFromParent(EditorJoint* parent);


		// Generate joint name
		string _generatedJointName();


		// Forward kinematics
		void _FK();

	} EditorSkeleton;
};

#endif