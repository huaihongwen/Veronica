#include "veMesh.h"

namespace vee {

	//---------------------------------------------------------------
	Mesh::Mesh(int vertNum) {

		// Vertex number
		mVertNum = vertNum;

		// Current vertex number
		mCurVertNum = 0;


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
	 * Push vertex
	 * @v {Vertex*} input vertex.
	 */
	void Mesh::pushVertex(Vertex* v) {

		// Copy data
		memcpy(mData + mCurVertNum*sizeof(Vertex), v, sizeof(Vertex));

		mCurVertNum++;
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