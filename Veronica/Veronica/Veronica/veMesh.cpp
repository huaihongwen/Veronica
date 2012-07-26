#include "veMesh.h"

namespace vee {

	//---------------------------------------------------------------
	Mesh::Mesh(int vertNum) {

		// Vertex number
		mVertNum = vertNum;

		// Current geometry number
		mCurGeometryNum = 0;

		// Current lighting number
		mCurLightingNum = 0;


		if (!vertNum) {

			// Empty data
			mData = NULL;
		} else {

			// Allocate memory
			mData = (uchar*)malloc(sizeof(Vertex) * vertNum);
		}
	}

	//---------------------------------------------------------------
	Mesh::~Mesh() {

		if (mData) {

			// Free memory
			free(mData);
		}
	}


	//---------------------------------------------------------------
	/**
	 * Push vertex geometry
	 * @v {Vertex*} input vertex.
	 */
	void Mesh::pushVertexGeometry(Vertex* v) {

		// Copy data
		memcpy(mData + mCurGeometryNum*sizeof(Vertex), v, sizeof(Vertex));

		mCurGeometryNum++;
	}

	//---------------------------------------------------------------
	/**
	 * Push vertex lighting
	 * @ao {float} vertex ambient occlusion.
	 */
	void Mesh::pushVertexLighting(float ao) {

		uchar* p = mData + mCurLightingNum*sizeof(Vertex);
		((Vertex*)p)->mAO = ao;

		mCurLightingNum++;
	}


	//---------------------------------------------------------------
	/**
	 * Get data
	 */
	uchar* Mesh::getData() {
		return mData;
	}


	//---------------------------------------------------------------
	/**
	 * Get vertex number
	 */
	int Mesh::getVertNum() {
		return mVertNum;
	}

	//---------------------------------------------------------------
	/**
	 * Set translate
	 */
	void Mesh::setTransform(float x, float y, float z) {

		mTransform = Transform::getTranslationMatrix(Vector3(x, y, z));
	}

	//---------------------------------------------------------------
	/**
	 * Get transform matrix
	 */
	Transform Mesh::getTransform() {
		return mTransform;
	}
};