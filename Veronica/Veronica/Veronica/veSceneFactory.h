#ifndef VEE_SCENEFACTORY_H
#define VEE_SCENEFACTORY_H

/*
 * veSceneFactory.h
 */

// Engine
#include "vePrerequisites.h"
#include "veUtils.h"
#include "veRay.h"
#include "veChunkSerializer.h"
#include "veLightingEngine.h"


// Editor
// Factory history
#include "veFactoryHistory.h"

#include <vector>

namespace vee {

	/**
	 * Scene factory mode
	 */
	typedef enum SceneFactoryMode {

		// Add voxel
		SFM_ADD,

		// Remove voxel
		SFM_REMOVE,

		// Edit
		SFM_EDIT,

		// Select
		SFM_SELECT

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
		 * Init
		 */
		void init();

		/**
		 * Destroy
		 */
		void destroy();


	protected:
		/**
		 * Bind events
		 */
		void _bindEvents();

		/**
		 * Unbind events
		 */
		void _unbindEvents();

		/**
		 * On color panel select
		 */
		bool _onColorPanelSelect(float* c);

		/**
		 * On texture panel select
		 */
		bool _onTexturePanelSelect(VoxelType t);


	public:
		/**
		 * Mouse left button up
		 */
		void mouseLUp(int x, int y);

		/**
		 * Key pressed
		 */
		void keyPressed(WPARAM key);


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

		/**
		 * Restore
		 */
		OperationSnapshot* _restore(OperationSnapshot* oldOS);


	protected:
		// Scene
		Scene mScene;
		

		// Factory history
		FactoryHistory mHistory;


		// Events
		// Texture panel event handler id
		int mTexturePanelEventHandlerId;

		// Color panel event handler id
		int mColorPanelEventHandlerId;


		// Edit related logic
		// Scene factory mode
		SceneFactoryMode mMode;


		// Current voxel color
		uchar mCurVoxelColor[3];

		// Current voxel type
		VoxelType mCurVoxelType;



		// Meshes
		// TODO: Better scene meshes management.
		// Chunk serializer
		ChunkSerializer mChunkSerializer;

		// Scene meshes array
		vector<Mesh*> mSceneMeshesArray;


	public:
		// Pointer to editor
		Editor* mParent;
	};
};

#endif