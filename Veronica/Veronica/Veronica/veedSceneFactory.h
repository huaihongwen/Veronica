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

// Factory history
#include "veedFactoryHistory.h"

#include <vector>

namespace veed {

	/**
	 * Scene factory mode
	 */
	typedef enum SceneFactoryMode {

		// Add voxel
		SFM_ADD,

		// Remove voxel
		SFM_REMOVE

	} SceneFactoryMode;


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

		/**
		 * Handle key pressed
		 */
		void handleKeyPressed(WPARAM key);


	protected:
		/**
		 * Edit voxel
		 */
		void _editVoxel(int* iInfo);

		/**
		 * Target voxel info
		 */
		void _targetVoxelInfo(int* iInfo, int* tInfo);


		/**
		 * Refresh meshes
		 */
		void _refreshMeshes(int i, int j, int k);

		/**
		 * Refresh chunk mesh
		 */
		void _refreshChunkMesh(uint i);


		/**
		 * Undo
		 */
		void _undo();

		/**
		 * Redo
		 */
		void _redo();


	protected:
		// Scene
		Scene mScene;

		// Factory history
		FactoryHistory mHistory;


		// Edit related logic

		// Scene factory mode
		SceneFactoryMode mMode;



		// Meshes
		// TODO: Better scene meshes management.
		// Chunk serializer
		ChunkSerializer mChunkSerializer;

		// Scene meshes array
		vector<Mesh*> mSceneMeshesArray;
	};
};

#endif