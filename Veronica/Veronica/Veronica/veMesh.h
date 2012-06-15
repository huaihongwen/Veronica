#ifndef VEE_MESH_H
#define VEE_MESH_H

/*
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
	 * Mesh contains an array of interleaved vertex data.
	 */
	class Mesh {

	public:
		Mesh(int vertNum=0);
		~Mesh();


	public:
		/**
		 * Push vertex geometry
		 */
		void pushVertexGeometry(Vertex* v);

		/**
		 * Push vertex lighting
		 */
		void pushVertexLighting(float ao);


		/**
		 * Get data
		 */
		uchar* getData();

		/**
		 * Get vertex number
		 */
		int getVertNum();


		/**
		 * Set transform matrix
		 */
		void setTransform(float x, float y, float z);

		/**
		 * Get transform matrix
		 */
		Transform getTransform();

	protected:
		// Vertex number
		int mVertNum;

		// Current geometry number
		int mCurGeometryNum;

		// Current lighting number
		int mCurLightingNum;


		// Vertex data
		uchar* mData;


		// Transform matrix
		Transform mTransform;
	};
};

#endif