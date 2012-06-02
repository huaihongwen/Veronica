#ifndef VEED_SCENEFACTORY_H
#define VEED_SCENEFACTORY_H

/*
 * veedSceneFactory.h
 */

#include "veedPrerequisites.h"

// Engine
// Utils
#include "veUtils.h"
// Ray
#include "veRay.h"
// Chunk serializer
#include "veChunkSerializer.h"

#include <vector>

namespace veed {

	/**
	 * Scene factory
	 */
	class SceneFactory {

	public:
		SceneFactory();
		~SceneFactory();


	public:
		/**
		 * Init scene
		 */
		void initScene();


	public:
		/**
		 * Handle mouse click
		 */
		void handleMouseClick(int wx, int wy);


	protected:
		/**
		 * Edit voxel
		 */
		void _editVoxel(int* selectedVoxelInfo);

		/**
		 * Refresh mesh
		 */
		void _refreshMesh(uint index);


	protected:
		// Scene
		Scene mScene;


		// Meshes
		// TODO: Better scene meshes management.
		// Chunk serializer
		ChunkSerializer mChunkSerializer;

		// Scene meshes array
		vector<Mesh*> mSceneMeshesArray;


		// Edit related logic
	};
};

#endif