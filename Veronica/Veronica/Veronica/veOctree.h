#ifndef VEE_OCTREE_H
#define VEE_OCTREE_H

/*
 * veOctree.h
 * Basic octree datastructures
 */

#include "vePrerequisites.h"
#include "veBoundingBox.h"

namespace vee {

	// Octree node
	struct OctreeNode{

		// Bounding box
		BBox mBB;
		// 8 children pointers
		OctreeNode* mChildren[8];
		// Tree level, 0: root
		uint mLevel;

		// Constructor
		OctreeNode() {
			// No children
			for (int i = 0; i < 8; i++) {
				mChildren[i] = NULL;
			}

			// Default level 0
			mLevel = 0;
		}
		OctreeNode(BBox& bb, uint level) {
			mBB = bb;
			// No children
			for (int i = 0; i < 8; i++) {
				mChildren[i] = NULL;
			}
			mLevel = level;
		}
		~OctreeNode() {}
	};

	// Recursively delete an octree
	//void deleteOctree(OctreeNode* root);
};

#endif