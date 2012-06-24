#ifndef VEE_VOXEL_H
#define VEE_VOXEL_H

/*
 * veVoxel.h
 */

#include "vePrerequisites.h"

namespace vee {

	/**
	 * Voxel type
	 */
	typedef enum VoxelType {
		
		// Default
		VT_DEFAULT,


		// Air
		VT_AIR,

		
		// Purple brick
		VT_PURPLEBRICK,
		
		// Yellow brick
		VT_YELLOWBRICK

	} VoxelType;


	/**
	 * Voxel
	 */
	typedef struct Voxel {

		// Type
		VoxelType mType;

		// Color
		uchar mColor[4];


		//---------------------------------------------------------------
		Voxel();
		Voxel(Voxel& v);
		~Voxel();

	} Voxel;


	/**
	 * Volume
	 * Volume defines a local coordinate space, it has
	 * a world space position and size.
	 */
	typedef struct Volume {

		// World position
		int mPos[3];

		// Size
		int mSize[3];


		//---------------------------------------------------------------
		/**
		 * Check whether this volume contains
		 * a coordinate or not.
		 */
		bool contain(int i, int j, int k) {
			
			if (i < 0 || i >= mSize[0] ||
				j < 0 || j >= mSize[1] ||
				k < 0 || k >= mSize[2]) {

				return false;
			} else {
				
				return true;
			}
		}

	} Volume;


	/**
	 * Chunk
	 * Chunk contains a volume and a "3D(represented as 1D)" array
	 * of voxels, the "3D size" of the array should be exact same as
	 * the volume size.
	 */
	typedef struct Chunk {

		// Volume
		Volume mVolume;

		// Voxel array
		Voxel** mData;


		//---------------------------------------------------------------
		Chunk();
		~Chunk();


		/**
		 * Init
		 */
		void init(int sx, int sy, int sz, int px=0, int py=0, int pz=0);

		/**
		 * Get voxel
		 */
		Voxel* getVoxel(int i, int j, int k);

		/**
		 * Set voxel
		 */
		void setVoxel(int i, int j, int k, Voxel* v);

	} Chunk;





	







	













};

#endif