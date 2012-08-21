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

// Editor
// Factory history
#include "veFactoryHistory.h"


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


	protected:
		/**
		 * Clean
		 */
		void _clean();


	public:
		/**
		 * Init
		 */
		void init(Chunk* c, Mesh* m, FactoryHistory* h);

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


	public:
		/**
		 * Mouse left button down
		 */
		void mouseLDown(int x, int y);

		/**
		 * Mouse left button up
		 */
		void mouseLUp(int x, int y);

		/**
		 * Mouse move
		 */
		void mouseMove(int x, int y);


		/**
		 * Key pressed
		 */
		void keyPressed(WPARAM key);


	protected:
		/**
		 * Intersection test
		 */
		bool _intersectionTest(int x, int y, int* result);


		/**
		 * Process operation volume on chunk copy
		 */
		void _processOperationVolume();


		/**
		 * Apply OperationSnapshot
		 */
		void _applyOpSs(Chunk* c, OperationSnapshot* opSs);

		/**
		 * Take OperationSnapshot
		 */
		OperationSnapshot* _takeOpSs(Chunk* c, OperationSnapshot* refOpSs);


		/**
		 * Undo
		 */
		void _undo();

		/**
		 * Redo
		 */
		void _redo();


	protected:
		// Input data
		// Chunk
		Chunk* _mChunk;

		// Chunk mesh
		Mesh* _mMesh;

		// Factory history
		FactoryHistory* _mHistory;


		// Edit related data
		// Current OperationSnapshot
		OperationSnapshot* _mOpSsCur;

		// Color selection event handler id
		int mColorSelectionEvtHandlerId;

		// Chunk copy
		Chunk* _mChunkCopy;

		// Params
		// Scene factory mode
		SceneFactoryMode _mMode;

		// Current voxel color
		uchar _mVoxelColorCur[3];

		// Current voxel type
		VoxelType _mVoxelTypeCur;


		// Intersection flag
		bool _mIstFlag;

		// Operation flag
		bool _mOpFlag;


		// Intersection data
		// Format: chunk space i, j, k, faceIndex
		// Intersection "from"
		int _mIstFrom[4];

		// Intersection "to"
		int _mIstTo[4];

		// Current intersection
		int _mIstCur[4];


		// Events
		// Color panel event handler id
		int _mColorPanelEventHandlerId;


	public:
		// Pointer to editor
		Editor* mParent;

		// Chunk serializer
		ChunkSerializer mSerializer;
	};
};

#endif