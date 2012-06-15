#ifndef VEE_CHUNKSERIALIZER_H
#define VEE_CHUNKSERIALIZER_H

/**
 * veChunkSerializer.h
 */

#include "vePrerequisites.h"
#include "veRay.h"
#include "veScene.h"
#include "veMesh.h"
#include "veUtils.h"

#include <vector>

namespace vee {

	/**
	 * Chunk serializer
	 * Serialize chunk into model space mesh.
	 */
	class ChunkSerializer {

	public:
		ChunkSerializer();
		~ChunkSerializer();


	public:
		/**
		 * Set scene 
		 */
		void setScene(Scene* s);

		/**
		 * Chunk serializer
		 */
		Mesh* serialize(Chunk* chunk);

	protected:
		/**
		 * Calculate chunk vertex number
		 */
		int _vertNum(Chunk* chunk);

		/**
		 * Serialize voxel face
		 */
		void _serializeVoxelFace(int i, int j, int k, Chunk* chunk,
			int faceIndex, Mesh* m);

		/**
		 * Face position
		 */
		void _facePosition(int i, int j, int k, int faceIndex,
			Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3);
		/**
		 * Face normal
		 */
		void _faceNormal(int faceIndex,
			Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3);

		/**
		 *
		 */


	protected:
		// Pointer to scene
		Scene* mScene;



	// TODO: Lighting system
	protected:
		/**
		 * Face ambient occlusion
		 */
		void _faceAmbientOcclusion(int i, int j, int k, int faceIndex, Mesh* m);
	};
};


#endif