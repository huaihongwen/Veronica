#include "veOctree.h"

namespace vee {

	/* Recursively delete an octree, this function would keep the "root", manually delete it
	 * after this function call
	 * @param root {OctreeNode*} root of the tree or sub-tree;
	 */
	/*
	void deleteOctree(OctreeNode* root) {

		// For each child
		for (int i = 0; i < 8; i++) {

			// If we dont have this child
			if (!root->mChildren[i]) {

				// Do nothing
				continue;
			} else {

				// Recursive delete this child's sub-tree
				deleteOctree(root->mChildren[i]);
				// Delete this child
				delete root->mChildren[i];
			}
		}
	}
	*/
};