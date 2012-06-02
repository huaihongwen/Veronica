#ifndef VEED_SKELETONFACTORY_H
#define VEED_SKELETONFACTORY_H


/*
 * veedSkeletonFactory.h
 */


#include "veedPrerequisites.h"


// Engine

// Ray
#include "veRay.h"

// Skeleton
#include "veSkeleton.h"


namespace veed {

	// Skeleton factory mode
	typedef enum SkeletonFactoryMode {

		// Select mode
		SFM_SELECT,

		// Edit mode
		SFM_EDIT

	} SkeletonFactoryMode;



	// Skeleton factory
	class SkeletonFactory {

	public:
		SkeletonFactory();
		~SkeletonFactory();


	public:
		// Mouse click
		void handleMouseClick(int x, int y);

		// Mouse move
		void handleMouseMove(float dx, float dy);


		// Key up
		//void handleKeyPressed(WPARAM key);


	public:
		// Create skeleton
		void createSkeleton();


		// Render
		void render();


	protected:
		// Intersection test
		//void _intersectionTest(int wx, int wy);


	protected:
		// Skeleton factory mode
		SkeletonFactoryMode mMode;


		// Editor skeleton
		EditorSkeleton* mSkeleton;
	};

};

#endif