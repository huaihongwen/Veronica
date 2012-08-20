#ifndef VEE_MESH_H
#define VEE_MESH_H

/**
 * veMesh.h
 */

#include "vePrerequisites.h"
#include "veTransform.h"


namespace vee {

	/**
	 * Vertex
	 */
	typedef struct Vertex {

		// Geometry information
		// Position
		float mPos[3];

		// Normal
		float mNormal[3];

		// Texcoord0
		float mTexcoord[2];


		// Color
		uchar mColor[4];


		// Lighting information
		// Ambient occlusion
		float mAO;

	} Vertex;



	/**
	 * Mesh
	 */
	class Mesh {

	public:
		Mesh();
		~Mesh();


	public:
		/**
		 * Init
		 */
		void init(int num);

		/**
		 * Destroy
		 */
		void destroy();


		/**
		 * Reset
		 */
		void reset();


	public:
		/**
		 * Push vertex geometry
		 */
		void pushVertexGeometry(Vertex* v);


		/**
		 * Push vertex lighting
		 */
		void pushVertexLighting(float ao);


	public:
		/**
		 * Get data
		 */
		uchar* getData();

		/**
		 * Get vertex number
		 */
		int getVertNum();


		/**
		 * Set transform
		 */
		void setTransform(float x, float y, float z);

		/**
		 * Get transform
		 */
		Transform getTransform();


	protected:
		// Max vertex number
		int _mVertNumMax;

		// Current vertex number
		int _mVertNumCur;


		// Current geometry index
		int _mGeoIdx;

		// Current lighting index
		int _mLightingIdx;


		// Vertex data
		uchar* _mData;


		// Transform matrix
		Transform _mTransform;
	};
};

#endif