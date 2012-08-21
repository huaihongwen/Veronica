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
		
		// Air
		VT_AIR,


		// Default
		VT_DEFAULT,


		// Purple brick
		VT_PURPLE_BRICK,

		// Yellow brick
		VT_YELLOW_BRICK,

		// Grey brick 1
		VT_GREY_BRICK_1,

		// Grey brick 2
		VT_GREY_BRICK_2,

		// Grey brick 3
		VT_GREY_BRICK_3,

		// Grey brick 4
		VT_GREY_BRICK_4,

		// Grey brick 5
		VT_GREY_BRICK_5,

		// Grey brick 6
		VT_GREY_BRICK_6,

		// Grey brick 7
		VT_GREY_BRICK_7,

		// Grey brick 8
		VT_GREY_BRICK_8,

		// Grey brick 9
		VT_GREY_BRICK_9,


		// Grey metal
		VT_GREY_METAL,

		// Green blue metal
		VT_GREENBLUE_METAL,

		// Dark purple metal
		VT_DARKPURPLE_METAL,

		// Dark blue metal
		VT_DARKBLUE_METAL,

		// Brown metal
		VT_BROWN_METAL,

		// Dark green metal
		VT_DARKGREEN_METAL,

		// Dark red metal
		VT_DARKRED_METAL,

		// Black metal
		VT_BLACK_METAL,


		// Dark light
		VT_DARK_LIGHT,

		// Bright light
		VT_BRIGHT_LIGHT

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
		Voxel(VoxelType t, uchar* c);
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
		void init(Chunk* c);

		/**
		 * Init
		 */
		void init(int sx, int sy, int sz, int px=0, int py=0, int pz=0);

		/**
		 * Init
		 */
		void init(char* fileName);


		/**
		 * Destroy
		 */
		void destroy();


		/**
		 * Save to file
		 */
		void saveToFile(char* fileName);


		/**
		 * Get voxel
		 */
		bool getVoxel(int i, int j, int k, Voxel*& v);

		/**
		 * Set voxel
		 */
		void setVoxel(int i, int j, int k, Voxel* v);

	} Chunk;
};

#endif