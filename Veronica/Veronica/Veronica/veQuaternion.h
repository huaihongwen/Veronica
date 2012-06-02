#ifndef VEE_QUATERNION_H
#define VEE_QUATERNION_H


/*
 * veQuaternion.h
 */


#include "vePrerequisites.h"
#include "veTransform.h"


namespace vee {

	// Quaternion
	class Quaternion {

	public:
		real m_floats[4];


	public:
		Quaternion() {

			m_floats[0] = 0.0f;
			m_floats[1] = 0.0f;
			m_floats[2] = 0.0f;
			m_floats[3] = 0.0f;
		}
		Quaternion(const real& x, const real& y, const real& z, const real& w) {
		
			m_floats[0] = x;
			m_floats[1] = y;
			m_floats[2] = z;
			m_floats[3] = w;
		}


	public:

		// Set value
		void setValue(const real& x, const real& y, const real& z) {

			m_floats[0] = x;
			m_floats[1] = y;
			m_floats[2] = z;
			m_floats[3] = 0.0f;
		}

		// Set value
		void setValue(const real& x, const real& y, const real& z, const real& w) {

			m_floats[0] = x;
			m_floats[1] = y;
			m_floats[2] = z;
			m_floats[3] = w;
		}

		// Length
		real magnitude() {

			return sqrt(m_floats[0] * m_floats[0] + m_floats[1] * m_floats[1] + m_floats[2] * m_floats[2] + m_floats[3] * m_floats[3]); 
		}


		// From axis angle
		void fromAxisAngle(real radian, Vector3& axis) {

			// Normalize axis
			Vector3 a = axis;
			a.normalize();

			float s = sin(radian * 0.5f);
			float c = cos(radian * 0.5f);

			m_floats[0] = s*a[0];
			m_floats[1] = s*a[1];
			m_floats[2] = s*a[2];

			m_floats[3] = c;
		}


		// To matrix
		Transform toMatrix() {

			Transform result;

			float x = m_floats[0];
			float y = m_floats[1];
			float z = m_floats[2];
			float w = m_floats[3];


			result.m_basic[0][0] = 1.0f - 2.0f*y*y - 2.0f*z*z;
			result.m_basic[0][1] = 2.0f*x*y + 2.0f*w*z;
			result.m_basic[0][2] = 2.0f*x*z - 2*w*y;

			result.m_basic[1][0] = 2.0f*x*y - 2.0f*w*z;
			result.m_basic[1][1] = 1.0f - 2.0f*x*x - 2.0f*z*z;
			result.m_basic[1][2] = 2.0f*y*z + 2.0f*w*x;

			result.m_basic[2][0] = 2.0f*x*z + 2.0f*w*y;
			result.m_basic[2][1] = 2.0f*y*z - 2.0f*w*x;
			result.m_basic[2][2] = 1.0f - 2.0f*x*x - 2.0f*y*y;

			return result;
		}


		// From euler angle
		void fromEulerYXZ(const real& eulerY, const real& eulerX, const real& eulerZ) {

			float halfY = eulerY * 0.5f;
			float halfX = eulerX * 0.5f;
			float halfZ = eulerZ * 0.5f;


			m_floats[0] = cos(halfY)*sin(halfX)*cos(halfZ) + sin(halfY)*cos(halfX)*sin(halfZ);
			m_floats[1] = sin(halfY)*cos(halfX)*cos(halfZ) - cos(halfY)*sin(halfX)*sin(halfZ);
			m_floats[2] = cos(halfY)*cos(halfX)*sin(halfZ) - sin(halfY)*sin(halfX)*cos(halfZ);
			m_floats[3] = cos(halfY)*cos(halfX)*cos(halfZ) + sin(halfY)*sin(halfX)*sin(halfZ);
		}


		// Normalize
		void normalize() {

			real invMag = 1.0f / magnitude();

			m_floats[0] *= invMag;
			m_floats[1] *= invMag;
			m_floats[2] *= invMag;
			m_floats[3] *= invMag;
		}

		// Invert quaternion
		void invert() {
			
			m_floats[0] = - m_floats[0];
			m_floats[1] = - m_floats[1];
			m_floats[2] = - m_floats[2];
		}


		// Operator []
		real& operator [] (int idx) {
			return m_floats[idx];
		}
		// Operator []
		const real& operator [] (int idx) const { 
			return m_floats[idx];
		}


		friend Quaternion operator * (const Quaternion& q, const Vector3& v);
		friend Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	};


	// Rotate point by quaternion
	Vector3 Quaternion_rotatePoint (const Quaternion& q, const Vector3& v);
};

#endif