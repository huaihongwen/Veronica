#include "veMesh.h"

namespace vee {

	//---------------------------------------------------------------
	Mesh::Mesh() {

		// Vertex data
		_mData = NULL;
	}

	//---------------------------------------------------------------
	Mesh::~Mesh() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 * @num {int} max vertex number.
	 */
	void Mesh::init(int num) {

		// Max vertex number
		_mVertNumMax = num;

		// Current vertex number
		_mVertNumCur = 0;


		// Current geometry index
		_mGeoIdx = 0;

		// Current lighting index
		_mLightingIdx = 0;


		// Allocate data
		_mData = (uchar*)malloc(sizeof(Vertex) * _mVertNumMax);
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void Mesh::destroy() {

		if (_mData) {

			// Free data
			free(_mData);
		}
	}


	//---------------------------------------------------------------
	/**
	 * Reset
	 */
	void Mesh::reset() {

		// Current vertex number
		_mVertNumCur = 0;


		// Current geometry index
		_mGeoIdx = 0;;

		// Current lighting index
		_mLightingIdx = 0;
	}


	//---------------------------------------------------------------
	/**
	 * Push vertex geometry
	 * @v {Vertex*} input vertex.
	 */
	void Mesh::pushVertexGeometry(Vertex* v) {

		// Copy data
		memcpy(_mData + _mGeoIdx * sizeof(Vertex), v, sizeof(Vertex));

		// Current geometry index
		_mGeoIdx++;


		// Current vertex number
		_mVertNumCur++;
	}

	//---------------------------------------------------------------
	/**
	 * Push vertex lighting
	 * @ao {float} vertex ambient occlusion.
	 */
	void Mesh::pushVertexLighting(float ao) {

		uchar* p = _mData + _mLightingIdx * sizeof(Vertex);
		((Vertex*)p)->mAO = ao;

		// Current lighting index
		_mLightingIdx++;
	}


	//---------------------------------------------------------------
	/**
	 * Get data
	 */
	uchar* Mesh::getData() {
		return _mData;
	}

	//---------------------------------------------------------------
	/**
	 * Get vertex number
	 */
	int Mesh::getVertNum() {
		return _mVertNumCur;
	}


	//---------------------------------------------------------------
	/**
	 * Set transform
	 */
	void Mesh::setTransform(float x, float y, float z) {

		_mTransform = Transform::getTranslationMatrix(Vector3(x, y, z));
	}

	//---------------------------------------------------------------
	/**
	 * Get transform
	 */
	Transform Mesh::getTransform() {
		return _mTransform;
	}
};