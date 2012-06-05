#include "veChunkSerializer.h"

namespace vee {

	//---------------------------------------------------------------
	ChunkSerializer::ChunkSerializer() {
	}

	//---------------------------------------------------------------
	ChunkSerializer::~ChunkSerializer() {
	}

	//---------------------------------------------------------------
	/**
	 * Set scene 
	 */
	void ChunkSerializer::setScene(Scene* s) {
		mScene = s;
	}

	//---------------------------------------------------------------
	/**
	 * Chunk serializer
	 * Serialize chunk into model space mesh.
	 * @chunk {Chunk*} input chunk.
	 * @return {Mesh*} model space mesh.
	 */
	Mesh* ChunkSerializer::serialize(Chunk* chunk) {

		// Vertex number
		int vertNum = _vertNum(chunk);

		//if (DEBUGMODE) {
		//	cout<<"[ChunkSerializer]:<<  Vertex Number: "<<vertNum<<endl;
		//}

		// Mesh
		Mesh* m = new Mesh(vertNum);


		// Chunk volume size
		int sx = chunk->mVolume.mSize[0];
		int sy = chunk->mVolume.mSize[1];
		int sz = chunk->mVolume.mSize[2];

		// Chunk volume pos
		int px = chunk->mVolume.mPos[0];
		int py = chunk->mVolume.mPos[1];
		int pz = chunk->mVolume.mPos[2];

		// Converted world space coordinate
		int wCoord[3];

		// Voxel
		Voxel* v = NULL;

		// Loop each coordinate
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					// Converted world space coordinate
					wCoord[0] = i + px;
					wCoord[1] = j + py;
					wCoord[2] = k + pz;

					if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2], v) || !v) {

						// Empty voxel
						continue;
					} else {

						// Check 6 neighbor voxels

						// Neighbor 0
						if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2]-1, v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 0, m);
						}

						// Neighbor 2
						if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2]+1, v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 2, m);
						}

						// Neighbor 1
						if (!mScene->getVoxel(wCoord[0]-1, wCoord[1], wCoord[2], v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 1, m);
						}

						// Neighbor 3
						if (!mScene->getVoxel(wCoord[0]+1, wCoord[1], wCoord[2], v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 3, m);
						}

						// Neighbor 4
						if (!mScene->getVoxel(wCoord[0], wCoord[1]-1, wCoord[2], v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 4, m);
						}

						// Neighbor 5
						if (!mScene->getVoxel(wCoord[0], wCoord[1]+1, wCoord[2], v) || !v) {
							_serializeVoxelFace(i, j, k, chunk, 5, m);
						}
					}
				}
			}
		}

		m->setTransform((float)chunk->mVolume.mPos[0],
			(float)chunk->mVolume.mPos[1], (float)chunk->mVolume.mPos[2]);

		return m;
	}

	//---------------------------------------------------------------
	/**
	 * Calculate chunk vertex number
	 * @chunk {Chunk*} input chunk.
	 * @return {int} vertex number.
	 */
	int ChunkSerializer::_vertNum(Chunk* chunk) {

		// Vertex number
		int vertNum = 0;

		// Chunk volume size
		int sx = chunk->mVolume.mSize[0];
		int sy = chunk->mVolume.mSize[1];
		int sz = chunk->mVolume.mSize[2];

		// Chunk volume pos
		int px = chunk->mVolume.mPos[0];
		int py = chunk->mVolume.mPos[1];
		int pz = chunk->mVolume.mPos[2];

		// Converted world space coordinate
		int wCoord[3];

		// Voxel
		Voxel* v = NULL;

		// Loop each coordinate
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					// Converted world space coordinate
					wCoord[0] = i + px;
					wCoord[1] = j + py;
					wCoord[2] = k + pz;

					if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2], v) || !v) {

						// Empty voxel
						continue;
					} else {

						// Check 6 neighbor voxels

						// Neighbor 0
						if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2]-1, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 2
						if (!mScene->getVoxel(wCoord[0], wCoord[1], wCoord[2]+1, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 1
						if (!mScene->getVoxel(wCoord[0]-1, wCoord[1], wCoord[2], v) || !v) {
							vertNum += 6;
						}

						// Neighbor 3
						if (!mScene->getVoxel(wCoord[0]+1, wCoord[1], wCoord[2], v) || !v) {
							vertNum += 6;
						}

						// Neighbor 4
						if (!mScene->getVoxel(wCoord[0], wCoord[1]-1, wCoord[2], v) || !v) {
							vertNum += 6;
						}

						// Neighbor 5
						if (!mScene->getVoxel(wCoord[0], wCoord[1]+1, wCoord[2], v) || !v) {
							vertNum += 6;
						}
					}
				}
			}
		}

		return vertNum;
	}

	//---------------------------------------------------------------
	/**
	 * Serialize voxel face
	 * Serialize voxel face in chunk space.
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @chunk {Chunk*} input chunk.
	 * @faceIndex {int} face index.
	 * @m {Mesh*} model space mesh.
	 */
	void ChunkSerializer::_serializeVoxelFace(int i, int j, int k, Chunk* chunk,
		int faceIndex, Mesh* m) {
		
		// Vertices
		Vertex v0, v1, v2, v3;

		// Face position
		_facePosition(i, j, k, faceIndex, v0, v1, v2, v3);

		// Face normal
		_faceNormal(faceIndex, v0, v1, v2, v3);


		// Push vertices
		m->pushVertex(&v0);
		m->pushVertex(&v1);
		m->pushVertex(&v2);
		m->pushVertex(&v0);
		m->pushVertex(&v2);
		m->pushVertex(&v3);
	}

	//---------------------------------------------------------------
	/**
	 * Face position
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @faceIndex {int} face index.
	 * @v0 {Vertex&} input vertex v0.
	 * @v1 {Vertex&} input vertex v1.
	 * @v2 {Vertex&} input vertex v2.
	 * @v3 {Vertex&} input vertex v3.
	 */
	void ChunkSerializer::_facePosition(int i, int j, int k, int faceIndex,
		Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3) {

		// Voxel size
		float vs = 1.0f;

		// Base position
		float bp[3];
		bp[0] = i*vs; bp[1] = j*vs; bp[2] = k*vs;

		
		switch (faceIndex) {
			
		// Face 0
		case 0: {
			// Position
			v0.mPos[0] = bp[0]+vs; v0.mPos[1] = bp[1]+vs; v0.mPos[2] = bp[2];
			v1.mPos[0] = bp[0]+vs; v1.mPos[1] = bp[1]; v1.mPos[2] = bp[2];
			v2.mPos[0] = bp[0]; v2.mPos[1] = bp[1]; v2.mPos[2] = bp[2];
			v3.mPos[0] = bp[0]; v3.mPos[1] = bp[1]+vs; v3.mPos[2] = bp[2];
				}
				break;

		// Face 2
		case 2: {
			// Position
			v0.mPos[0] = bp[0]; v0.mPos[1] = bp[1]+vs; v0.mPos[2] = bp[2]+vs;
			v1.mPos[0] = bp[0]; v1.mPos[1] = bp[1]; v1.mPos[2] = bp[2]+vs;
			v2.mPos[0] = bp[0]+vs; v2.mPos[1] = bp[1]; v2.mPos[2] = bp[2]+vs;
			v3.mPos[0] = bp[0]+vs; v3.mPos[1] = bp[1]+vs; v3.mPos[2] = bp[2]+vs;
				}
				break;

		// Face 1
		case 1: {
			// Position
			v0.mPos[0] = bp[0]; v0.mPos[1] = bp[1]+vs; v0.mPos[2] = bp[2];
			v1.mPos[0] = bp[0]; v1.mPos[1] = bp[1]; v1.mPos[2] = bp[2];
			v2.mPos[0] = bp[0]; v2.mPos[1] = bp[1]; v2.mPos[2] = bp[2]+vs;
			v3.mPos[0] = bp[0]; v3.mPos[1] = bp[1]+vs; v3.mPos[2] = bp[2]+vs;
				}
				break;

		// Face 3
		case 3: {
			// Position
			v0.mPos[0] = bp[0]+vs; v0.mPos[1] = bp[1]+vs; v0.mPos[2] = bp[2]+vs;
			v1.mPos[0] = bp[0]+vs; v1.mPos[1] = bp[1]; v1.mPos[2] = bp[2]+vs;
			v2.mPos[0] = bp[0]+vs; v2.mPos[1] = bp[1]; v2.mPos[2] = bp[2];
			v3.mPos[0] = bp[0]+vs; v3.mPos[1] = bp[1]+vs; v3.mPos[2] = bp[2];
				}
				break;

		// Face 4
		case 4: {
			// Position
			v0.mPos[0] = bp[0]; v0.mPos[1] = bp[1]; v0.mPos[2] = bp[2]+vs;
			v1.mPos[0] = bp[0]; v1.mPos[1] = bp[1]; v1.mPos[2] = bp[2];
			v2.mPos[0] = bp[0]+vs; v2.mPos[1] = bp[1]; v2.mPos[2] = bp[2];
			v3.mPos[0] = bp[0]+vs; v3.mPos[1] = bp[1]; v3.mPos[2] = bp[2]+vs;
				}
				break;

		// Face 5
		case 5: {
			// Position
			v0.mPos[0] = bp[0]; v0.mPos[1] = bp[1]+vs; v0.mPos[2] = bp[2];
			v1.mPos[0] = bp[0]; v1.mPos[1] = bp[1]+vs; v1.mPos[2] = bp[2]+vs;
			v2.mPos[0] = bp[0]+vs; v2.mPos[1] = bp[1]+vs; v2.mPos[2] = bp[2]+vs;
			v3.mPos[0] = bp[0]+vs; v3.mPos[1] = bp[1]+vs; v3.mPos[2] = bp[2];
				}
				break;
		
		default:
			return;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Face normal
	 * @faceIndex {int} face index.
	 * @v0 {Vertex&} input vertex v0.
	 * @v1 {Vertex&} input vertex v1.
	 * @v2 {Vertex&} input vertex v2.
	 * @v3 {Vertex&} input vertex v3.
	 */
	void ChunkSerializer::_faceNormal(int faceIndex,
		Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3) {
			
		// Normal
		float n[3];
		
		switch (faceIndex) {
			
		// Face 0
		case 0:
			n[0] = 0.0f; n[1] = 0.0f; n[2] = -1.0f;
			break;

		// Face 2
		case 2:
			n[0] = 0.0f; n[1] = 0.0f; n[2] = 1.0f;
			break;

		// Face 1
		case 1:
			n[0] = -1.0f; n[1] = 0.0f; n[2] = 0.0f;
			break;

		// Face 3
		case 3:
			n[0] = 1.0f; n[1] = 0.0f; n[2] = 0.0f;
			break;

		// Face 4
		case 4:
			n[0] = 0.0f; n[1] = -1.0f; n[2] = 0.0f;
			break;

		// Face 5
		case 5:
			n[0] = 0.0f; n[1] = 1.0f; n[2] = 0.0f;
			break;

		default:
			n[0] = 0.0f; n[1] = 0.0f; n[2] = 1.0f;
			break;;
		}

		// Copy normal
		v0.mNormal[0] = n[0]; v0.mNormal[1] = n[1]; v0.mNormal[2] = n[2];
		v1.mNormal[0] = n[0]; v1.mNormal[1] = n[1]; v1.mNormal[2] = n[2];
		v2.mNormal[0] = n[0]; v2.mNormal[1] = n[1]; v2.mNormal[2] = n[2];
		v3.mNormal[0] = n[0]; v3.mNormal[1] = n[1]; v3.mNormal[2] = n[2];
	}
};