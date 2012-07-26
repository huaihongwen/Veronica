#ifndef VEE_RAY_H
#define VEE_RAY_H


/*
 * veRay.h
 */


#include "vePrerequisites.h"
#include "veBoundingBox.h"

namespace vee {

	// Ray
	class Ray {

	public:

		//---------------------------------------------------------------
		Ray() {

			// Origin
			mOri.setValue(0.0f, 0.0f, 0.0f);

			// Direction
			mDir.setValue(0.0f, 0.0f, -1.0f);
		}

		//---------------------------------------------------------------
		Ray(Vector3& origin, Vector3& dir) {

			// Origin
			mOri = origin;

			// Direction
			mDir = dir;
			mDir.normalize();
		}

		//---------------------------------------------------------------
		~Ray() {
		}


	public:
		//---------------------------------------------------------------
		// Get origin
		Vector3& getOrigin() {
			return mOri;
		}

		//---------------------------------------------------------------
		// Get direction
		Vector3& getDirection() {
			return mDir;
		}

		//---------------------------------------------------------------
		// Set origin
		void setOrigin(Vector3& origin) {
			mOri = origin;
		}

		//---------------------------------------------------------------
		// Set origin
		void setOrigin(float x, float y, float z) {
			mOri.setValue(x, y, z);
		}

		//---------------------------------------------------------------
		// Set direction
		void setDirection(Vector3& dir) {
			mDir = dir;
		}

		//---------------------------------------------------------------
		// Set direction
		void setDirection(float x, float y, float z) {
			mDir.setValue(x, y, z);
		}


	protected:
		// Origin
		Vector3 mOri;

		// Direction
		Vector3 mDir;
	};


	// Ray box intersection
	bool rayBoxIntersection(Ray& ray, BBox& box, float& tNear, float& tFar, int& fIdx);

	// Ray sphere intersection
	bool raySphereIntersection(Ray& ray, Vector3& center, float& radius);
};

#endif