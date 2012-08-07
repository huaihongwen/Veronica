#include "veChunkSerializer.h"
#include "veRay.h"
#include "veLightingEngine.h"

namespace vee {

	//---------------------------------------------------------------
	ChunkSerializer::ChunkSerializer() {
	}

	//---------------------------------------------------------------
	ChunkSerializer::~ChunkSerializer() {
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

		if (DEBUGMODE) {
			cout<<"[ChunkSerializer]:<<  Vertex Number: "<<vertNum<<endl;
		}

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


		// Voxel
		Voxel* curVoxel = NULL;
		Voxel* v = NULL;


		// Loop each coordinate
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					if (!chunk->getVoxel(i, j, k, curVoxel) || !curVoxel) {

						// Empty voxel
						continue;
					} else {

						// Check 6 neighbor voxels

						// Neighbor 0
						if (!chunk->getVoxel(i, j, k-1, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 0, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 0, m);
						}

						// Neighbor 2
						if (!chunk->getVoxel(i, j, k+1, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 2, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 2, m);
						}

						// Neighbor 1
						if (!chunk->getVoxel(i-1, j, k, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 1, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 1, m);
						}

						// Neighbor 3
						if (!chunk->getVoxel(i+1, j, k, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 3, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 3, m);
						}

						// Neighbor 4
						if (!chunk->getVoxel(i, j-1, k, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 4, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 4, m);
						}

						// Neighbor 5
						if (!chunk->getVoxel(i, j+1, k, v) || !v) {
							
							// Face geometry
							_serializeVoxelFace(curVoxel, i, j, k, chunk, 5, m);

							// Face ambient occlusion
							_faceAmbientOcclusion(i, j, k, chunk, 5, m);
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


		// Voxel
		Voxel* v = NULL;

		// Loop each coordinate
		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				for (int k = 0; k < sz; k++) {

					if (!chunk->getVoxel(i, j, k, v) || !v) {

						// Empty voxel
						continue;
					} else {

						// Check 6 neighbor voxels

						// Neighbor 0
						if (!chunk->getVoxel(i, j, k-1, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 2
						if (!chunk->getVoxel(i, j, k+1, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 1
						if (!chunk->getVoxel(i-1, j,k, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 3
						if (!chunk->getVoxel(i+1, j, k, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 4
						if (!chunk->getVoxel(i, j-1, k, v) || !v) {
							vertNum += 6;
						}

						// Neighbor 5
						if (!chunk->getVoxel(i, j+1, k, v) || !v) {
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
	 * @v {Voxel*} voxel data.
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @chunk {Chunk*} input chunk.
	 * @faceIndex {int} face index.
	 * @m {Mesh*} model space mesh.
	 */
	void ChunkSerializer::_serializeVoxelFace(Voxel* v, int i, int j, int k, Chunk* chunk,
		int faceIndex, Mesh* m) {

		// Vertices
		Vertex v0, v1, v2, v3;

		// Face position
		_facePosition(i, j, k, faceIndex, v0, v1, v2, v3);

		// Face normal
		_faceNormal(faceIndex, v0, v1, v2, v3);

		// Face texture coordinates
		_faceTextCoords(v->mType, faceIndex, v0, v1, v2, v3);

		// Face color
		_faceColor(v, v0, v1, v2, v3);


		// Push vertices
		m->pushVertexGeometry(&v0);
		m->pushVertexGeometry(&v1);
		m->pushVertexGeometry(&v2);
		m->pushVertexGeometry(&v0);
		m->pushVertexGeometry(&v2);
		m->pushVertexGeometry(&v3);
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
			break;
		}

		// Copy normal
		v0.mNormal[0] = n[0]; v0.mNormal[1] = n[1]; v0.mNormal[2] = n[2];
		v1.mNormal[0] = n[0]; v1.mNormal[1] = n[1]; v1.mNormal[2] = n[2];
		v2.mNormal[0] = n[0]; v2.mNormal[1] = n[1]; v2.mNormal[2] = n[2];
		v3.mNormal[0] = n[0]; v3.mNormal[1] = n[1]; v3.mNormal[2] = n[2];
	}

	//---------------------------------------------------------------
	/**
	 * Face texture coordinates
	 */
	void ChunkSerializer::_faceTextCoords(VoxelType t, int faceIndex,
		Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3) {

		// Texture coordinates
		float coords[8];

		// Get face texture coordinates
		Utils::getVoxelFaceTexCoords(t, faceIndex, coords);


		v0.mTexcoord[0] = coords[0];
		v0.mTexcoord[1] = coords[1];
		v1.mTexcoord[0] = coords[2];
		v1.mTexcoord[1] = coords[3];
		v2.mTexcoord[0] = coords[4];
		v2.mTexcoord[1] = coords[5];
		v3.mTexcoord[0] = coords[6];
		v3.mTexcoord[1] = coords[7];
	}

	//---------------------------------------------------------------
	/**
	 * Face color
	 */
	void ChunkSerializer::_faceColor(Voxel* v,
		Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3) {

		v0.mColor[0] = v->mColor[0];
		v0.mColor[1] = v->mColor[1];
		v0.mColor[2] = v->mColor[2];
		v0.mColor[3] = v->mColor[3];

		v1.mColor[0] = v->mColor[0];
		v1.mColor[1] = v->mColor[1];
		v1.mColor[2] = v->mColor[2];
		v1.mColor[3] = v->mColor[3];

		v2.mColor[0] = v->mColor[0];
		v2.mColor[1] = v->mColor[1];
		v2.mColor[2] = v->mColor[2];
		v2.mColor[3] = v->mColor[3];

		v3.mColor[0] = v->mColor[0];
		v3.mColor[1] = v->mColor[1];
		v3.mColor[2] = v->mColor[2];
		v3.mColor[3] = v->mColor[3];
	}



	//---------------------------------------------------------------
	/**
	 * Face ambient occlusion
	 * @i {int} chunk space x coordinate.
	 * @j {int} chunk space y coordinate.
	 * @k {int} chunk space z coordinate.
	 * @chunk {Chunk*} input chunk.
	 * @faceIndex {int} face index.
	 * @m {Mesh*} input mesh.
	 */
	void ChunkSerializer::_faceAmbientOcclusion(int i, int j, int k, Chunk* chunk, int faceIndex, Mesh* m) {

		// Vertices' ambient occlusion
		float ao0, ao1, ao2, ao3;
		ao0 = ao1 = ao2 = ao3 = 0.0f;

		// Ambient occlusion step
		float step = 0.25f;


		// Voxel
		Voxel* v;

		if (i == 1 && k == 1 && j == 1 && faceIndex == 4) {
			int aa = 0;
		}



		// Face index
		switch (faceIndex) {

		case 0:
			{
				// Vertex 0
				if (!chunk->getVoxel(i+1, j+1, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i+1, j, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j+1, k-1, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i+1, j, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j-1, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j, k-1, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i, j, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i, j-1, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i-1, j, k-1, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i, j+1, k-1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i, j, k-1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i-1, j, k-1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i-1, j+1, k-1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		case 1:
			{
				// Vertex 0
				if (!chunk->getVoxel(i-1, j+1, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j+1, k, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i-1, j, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j, k, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i-1, j, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i-1, j, k+1, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i-1, j+1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i-1, j, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i-1, j, k+1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i-1, j+1, k+1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		case 2:
			{
				// Vertex 0
				if (!chunk->getVoxel(i-1, j+1, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j+1, k+1, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i-1, j, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j-1, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j, k+1, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i, j, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i, j-1, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j, k+1, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i, j+1, k+1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i, j, k+1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j, k+1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k+1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		case 3:
			{
				// Vertex 0
				if (!chunk->getVoxel(i+1, j+1, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i+1, j, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i+1, j, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i+1, j, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i+1, j, k, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i+1, j, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j, k-1, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i+1, j+1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j, k-1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k-1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		case 4:
			{
				// Vertex 0
				if (!chunk->getVoxel(i-1, j-1, k+1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j-1, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j-1, k+1, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i-1, j-1, k, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j-1, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j-1, k-1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j-1, k, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i, j-1, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i, j-1, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k-1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i, j-1, k+1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i, j-1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j-1, k+1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		case 5:
			{
				// Vertex 0
				if (!chunk->getVoxel(i-1, j+1, k-1, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i-1, j+1, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j+1, k, v) || !v) {
					ao0 += step;
				}
				if (!chunk->getVoxel(i, j+1, k-1, v) || !v) {
					ao0 += step;
				}


				// Vertex 1
				if (!chunk->getVoxel(i-1, j+1, k, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i-1, j+1, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j+1, k+1, v) || !v) {
					ao1 += step;
				}
				if (!chunk->getVoxel(i, j+1, k, v) || !v) {
					ao1 += step;
				}


				// Vertex 2
				if (!chunk->getVoxel(i, j+1, k, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i, j+1, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k+1, v) || !v) {
					ao2 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k, v) || !v) {
					ao2 += step;
				}


				// Vertex 3
				if (!chunk->getVoxel(i, j+1, k-1, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i, j+1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k, v) || !v) {
					ao3 += step;
				}
				if (!chunk->getVoxel(i+1, j+1, k-1, v) || !v) {
					ao3 += step;
				}
			}
			break;

		default:
			break;
		}


		m->pushVertexLighting(ao0);
		m->pushVertexLighting(ao1);
		m->pushVertexLighting(ao2);
		m->pushVertexLighting(ao0);
		m->pushVertexLighting(ao2);
		m->pushVertexLighting(ao3);
	}
};