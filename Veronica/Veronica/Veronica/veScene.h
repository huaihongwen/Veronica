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
	#define SCENECHUNK_X 16
	#define SCENECHUNK_Y 16
	#define SCENECHUNK_Z 16



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
		 * Get voxel
		 */
		Voxel* getVoxel(int i, int j, int k);

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