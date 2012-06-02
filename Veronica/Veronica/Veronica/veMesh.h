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

		// Position
		float mPos[3];

		// Normal
		float mNormal[3];

		// Texcoord0
		float mTexcoord[2];


		// Color
		uchar mColor[4];

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
		 * Push vertex
		 */
		void pushVertex(Vertex* v);

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

		// Current vertex number
		int mCurVertNum;

		// Vertex data
		uchar* mData;


		// Transform matrix
		Transform mTransform;
	};
};

#endif