#ifndef VEE_BOUNDINGBOX_H
#define VEE_BOUNDINGBOX_H


/*
 * veBoundingBox.h
 */


#include "vePrerequisites.h"
// Vector3
#include "veVector3.h"


namespace vee {

	// Bounding box
	class BBox {

	public:

		//---------------------------------------------------------------
		BBox() {

			// Origin
			mOrigin.setValue(0.0f, 0.0f, 0.0f);

			// Size
			mSize.setValue(1.0f, 1.0f, 1.0f);
		}

		//---------------------------------------------------------------
		BBox(Vector3& origin, Vector3& size) {

			// Origin
			mOrigin = origin;

			// Size
			mSize = size;
		}

		//---------------------------------------------------------------
		// Copy constructor
		BBox(const BBox& bb) {

			// Origin
			mOrigin = bb.mOrigin;

			// Size
			mSize = bb.mSize;
		}

		//---------------------------------------------------------------
		~BBox() {
		}


		//---------------------------------------------------------------
		// Operator =
		void operator = (const BBox& bb) {

			// Origin
			mOrigin = bb.mOrigin;

			// Size
			mSize = bb.mSize;
		}

		//---------------------------------------------------------------
		// Get origin
		Vector3 getOrigin() {

			return mOrigin;
		}

		//---------------------------------------------------------------
		// Get size
		Vector3 getSize() {

			return mSize;
		}

		//---------------------------------------------------------------
		// Set origin
		void setOrigin(Vector3& ori) {

			mOrigin = ori;
		}

		//---------------------------------------------------------------
		// Set origin
		void setOrigin(float x, float y, float z) {

			mOrigin[0] = x;
			mOrigin[1] = y;
			mOrigin[2] = z;
		}

		//---------------------------------------------------------------
		// Set size
		void setSize(Vector3& size) {

			mSize = size;
		}

		//---------------------------------------------------------------
		// Set size
		void setSize(float x, float y, float z) {

			mSize[0] = x;
			mSize[1] = y;
			mSize[2] = z;
		}


	public:

		// Origin
		Vector3 mOrigin;

		// Size
		Vector3 mSize;
	};

};

#endif