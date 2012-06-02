#include "veedSkeletonFactory.h"


namespace veed {

	//---------------------------------------------------------------
	SkeletonFactory::SkeletonFactory() {

		// Skeleton factory mode
		mMode = SFM_SELECT;


		// Editor skeleton
		mSkeleton = NULL;
	}

	//---------------------------------------------------------------
	SkeletonFactory::~SkeletonFactory() {

		// Editor skeleton
		if (mSkeleton) {
			delete mSkeleton;
		}
	}



	//---------------------------------------------------------------
	/*
	 * Mouse click
	 * @param wx {int} x pos relative to window
	 * @param wy {int} y pos relative to window
	 */
	void SkeletonFactory::handleMouseClick(int wx, int wy) {

		switch (mMode) {

		// Select mode
		case SFM_SELECT:

			// Do intersection test
			//_intersectionTest(wx, wy);

			break;


		// Edit mode
		case SFM_EDIT:
			break;


		default:
			break;
		}
	}


	//---------------------------------------------------------------
	// Mouse move
	void SkeletonFactory::handleMouseMove(float dx, float dy) {

		//cout<<"[SkeletonFactory]<<: Mouse move:  "<<dx<<"  "<<dy<<endl;
	}


	//---------------------------------------------------------------
	// Key pressed
	/*
	void SkeletonFactory::handleKeyPressed(WPARAM key) {

		// Not in edit mode
		if (mMode != SFM_EDIT) {
			return;
		}
	}
	*/


	//---------------------------------------------------------------
	// Create skeleton
	void SkeletonFactory::createSkeleton() {

		if (mSkeleton) {
			cout<<"[SkeletonFactory]<<:   Skeleton existed."<<endl;
		}


		// Create editor skeleton
		mSkeleton = new EditorSkeleton();

		// Init editor skeleton
		mSkeleton->init("Skeleton");
	}


	//---------------------------------------------------------------
	// Render
	void SkeletonFactory::render() {

		// Render skeleton
		mSkeleton->render();
	}






	//---------------------------------------------------------------
	/*
	 * Intersection test
	 * @param wx {int} x pos relative to window
	 * @param wy {int} y pos relative to window
	 */
	/*
	void SkeletonFactory::_intersectionTest(int wx, int wy) {

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
	}
	*/
};