#ifndef VEED_SCENE_H
#define VEED_SCENE_H

/*
 * veScene.h
 */

#include "vePrerequisites.h"
#include "veVoxel.h"

#include <vector>

namespace vee {

	/**
	 * Scene chunk size
	 */
	#define SCENECHUNK_X 64
	#define SCENECHUNK_Y 64
	#define SCENECHUNK_Z 64



	/*
	 * Scene
	 * Scene defines the world space, it is divided into
	 * equal size chunks.
	 */
	class Scene {

	public:
		Scene();
		~Scene();


	public:
		/**
		 * Init
		 */
		void init(int sx=SCENECHUNK_X, int sy=SCENECHUNK_Y,
			int sz=SCENECHUNK_Z);


	public:
		/**
		 * Convert world space coordinate to chunk local space coordinate.
		 */
		bool worldCoordToChunkCoord(int i, int j, int k, int* cc);

		/**
		 * Test world space coordinate inside or not.
		 */
		bool testInside(int i, int j, int k);

		/**
		 * Get voxel
		 */
		bool getVoxel(int i, int j, int k, Voxel*& r);

		/**
		 * Set voxel
		 */
		void setVoxel(int i, int j, int k, Voxel* v);

		/**
		 * Get chunk array
		 */
		vector<Chunk*>* getChunkArray();

	protected:
		// Volume
		Volume mVolume;


		// Chunk volume size
		int mCVSize[3];

		// Chunk array
		vector<Chunk*> mChunkArray;
	};
};

#endif