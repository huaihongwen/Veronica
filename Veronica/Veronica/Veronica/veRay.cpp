#include "veRay.h"

namespace vee {

	//---------------------------------------------------------------
	/* Ray box intersection
	 *
	 * @param ray {Ray&} input ray
	 * @param box {BBox*} input AABB box
	 * @param tNear {float&} time result for near plane if test succeed
	 * @param tFar {float&} time result for far plane if test succeed
	 * @param fIdx {int&} intersection face idx 0: -x, 1: x, 2: -y, 3: y, 4: -z, 5: z
	 *
	 * @return {bool} test result
	 */
	bool rayBoxIntersection(Ray& ray, BBox& box, float& tNear, float& tFar, int& fIdx) {

		// Cache for speed
		float ro[3], rd[3], bo[3], bh[3];
		// Ray info
		ro[0] = ray.getOrigin()[0];
		ro[1] = ray.getOrigin()[1];
		ro[2] = ray.getOrigin()[2];
		rd[0] = ray.getDirection()[0];
		rd[1] = ray.getDirection()[1];
		rd[2] = ray.getDirection()[2];

		// Box info
		bo[0] = box.getOrigin()[0];
		bo[1] = box.getOrigin()[1];
		bo[2] = box.getOrigin()[2];
		bh[0] = bo[0] + box.getSize()[0];
		bh[1] = bo[1] + box.getSize()[1];
		bh[2] = bo[2] + box.getSize()[2];

		// Test for each pair of planes in x,y,z axises
		float t1, t2, temp;

		// Axis
		int axis;
		// Whether tNear for an axis is on negative direction
		int tNearDirection[3];
		tNearDirection[0] = tNearDirection[1] = tNearDirection[2] = 0;

		for (int i = 0; i < 3; i++) {

			// Parellel to plane
			if (rd[i] == 0.0f) {
				// Outside of range
				if (ro[i] < bo[i] || ro[i] > bh[i]) {
					return false;
				}
			} else {

				// Calculate t1 and t2
				t1 = (bo[i] - ro[i])/rd[i];
				t2 = (bh[i] - ro[i])/rd[i];

				// Swap t1 and t2?
				if (t1 > t2) {
					temp = t2; t2 = t1; t1 = temp;

					// Near time for this axis is the positive direction
					tNearDirection[i] = 1;
				}

				// First time initialize tNear and tFar
				if (!i) {
					tNear = t1; tFar = t2;

					// First time, x axis
					axis = i;
				}

				// Setup tNear and tFar, we want largest tNear and smallest tFar
				if (t1 > tNear) {
					tNear = t1;

					// Largest tNear is on the axis
					axis = i;
				}
				if (t2 < tFar) {
					tFar = t2;
				}

				// Test for this direction
				if (tNear > tFar) {
					// Box is missed by the ray
					return false;
				}
				if (tFar < 0.0f) {
					// Box is behind of the ray
					return false;
				}
			}
		}

		// Determine intersection face idx
		fIdx = axis * 2 + tNearDirection[axis];

		return true;
	}


	//---------------------------------------------------------------
	/* Ray sphere intersection
	 *
	 * @param ray {Ray&} input ray
	 * @param center {Vector3&} center of the sphere
	 * @param radius {float&} radius of the sphere
	 *
	 * @return {bool} test result
	 */
	bool raySphereIntersection(Ray& ray, Vector3& center, float& radius) {

		// Compute coefficients

		// A
		float a = dot(ray.getDirection(), ray.getDirection());

		// B
		float b = 2.0f*dot(ray.getDirection(), ray.getOrigin());

		// C
		float c = dot(ray.getOrigin(), ray.getOrigin()) - radius*radius;


		// Discriminate
		float d = b * b - 4.0f * a * c;


		if (d < 0.0f) {

			return false;
		} else {

			return true;
		}
	}
};