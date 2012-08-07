#ifndef VEED_SCENE_H
#define VEED_SCENE_H

/*
 * veScene.h
 */

#include "vePrerequisites.h"
#include "veVoxel.h"


namespace vee {

	/**
	 * Scene size
	 */
	#define SCENE_X 16
	#define SCENE_Y 16
	#define SCENE_Z 16



	/*
	 * Scene
	 * Scene defines the world space.
	 */
	class Scene {

	public:
		Scene();
		~Scene();


	public:
		/**
		 * Init
		 */
		void init(int sx=SCENE_X, int sy=SCENE_Y,
			int sz=SCENE_Z);

		/**
		 * Destroy
		 */
		void destroy();


	public:
		/*
		 * Save to file
		 */
		void save(char* fileName);

		/**
		 * Load from file
		 */
		void load(char* fileName);


	public:
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


	public:
		// Chunk
		Chunk mChunk;
	};
};

#endif