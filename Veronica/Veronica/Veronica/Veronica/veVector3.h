#ifndef VEE_VECTOR3_H
#define VEE_VECTOR3_H

/*
 * veVector3.h
 * 3/ 4 demensional column major vector, includes an un-used w component
 *    m_floats[0]   m_floats[1]   m_floats[2]   m_floats[w]
 */

#include "vePrerequisites.h"
#include "veMath.h"

namespace vee {

	// Vector 3
	class Vector3 {
	public:
		real m_floats[4];

	public:
		// Constructor
		Vector3() { 
			m_floats[0] = 0.0f;
			m_floats[1] = 0.0f;
			m_floats[2] = 0.0f;
		}
		Vector3(const real& x, const real& y, const real& z) { 
			m_floats[0] = x;
			m_floats[1] = y;
			m_floats[2] = z; 
		}
		Vector3(const Vector3& v) { 
			m_floats[0] = v.m_floats[0];
			m_floats[1] = v.m_floats[1];
			m_floats[2] = v.m_floats[2]; 
		}

		// Set value
		void setValue (const real& x, const real& y, const real& z) { 
			m_floats[0] = x;
			m_floats[1] = y;
			m_floats[2] = z; 
		}
		// Length
		real magnitude() { 
			return sqrt(m_floats[0] * m_floats[0] + m_floats[1] * m_floats[1] + m_floats[2] * m_floats[2]); 
		}
		// Normalize vector
		void normalize() { 
			real invMag = 1.0f / magnitude(); 
			m_floats[0] *= invMag;
			m_floats[1] *= invMag;
			m_floats[2] *= invMag; 
		}

		// [] operator
		real& operator [] (int idx) {
			return m_floats[idx];
		}
		const real& operator [] (int idx) const { 
			return m_floats[idx];
		}
		// = Vector3
		void operator = (const Vector3& v) {
			m_floats[0] = v.m_floats[0]; 
			m_floats[1] = v.m_floats[1]; 
			m_floats[2] = v.m_floats[2]; 
		}
		// == 
		bool operator == (const Vector3& v) { 
			return m_floats[0] == v.m_floats[0] && m_floats[1] == v.m_floats[1] && m_floats[2] == v.m_floats[2]; 
		}
		// +=
		void operator += (const Vector3& v) { 
			m_floats[0] += v.m_floats[0];
			m_floats[1] += v.m_floats[1];
			m_floats[2] += v.m_floats[2];
		}
		// -=
		void operator -= (const Vector3& v) {
			m_floats[0] -= v.m_floats[0]; 
			m_floats[1] -= v.m_floats[1]; 
			m_floats[2] -= v.m_floats[2];
		}
		// *=
		void operator *= (const real& k) { 
			m_floats[0] *= k; 
			m_floats[1] *= k; 
			m_floats[2] *= k;
		}
		// /=
		void operator /= (const real& k) {
			float invK = 1.0f / k;
			m_floats[0] *= invK;
			m_floats[1] *= invK;
			m_floats[2] *= invK;
		}

		// Friend functions
		friend Vector3 operator + (const Vector3& v1, const Vector3& v2);
		friend Vector3 operator - (const Vector3& v1, const Vector3& v2);
		friend Vector3 operator * (const Vector3& v, const real& k);
		friend Vector3 operator / (const Vector3& v, const real& k);
	
		// Dot product
		friend float dot(const Vector3& v1, const Vector3& v2);
		// Cross product
		friend Vector3 cross(const Vector3& v1, const Vector3& v2);
	};

	// Vector 4
	class Vector4: public Vector3 {
	public:
		// Constructor
		Vector4() : Vector3() { 
			m_floats[3] = 1.0f;
		}
		Vector4(const real& x, const real& y, const real& z, const real& w) : Vector3(x, y, z) {
			m_floats[3] = w; 
		}
		Vector4(const Vector4& v) { 
			m_floats[0] = v.m_floats[0];
			m_floats[1] = v.m_floats[1];
			m_floats[2] = v.m_floats[2]; 
			m_floats[3] = v.m_floats[3];
		}

		void setValue(const real& x, const real& y, const real&z, const real& w) { 
			m_floats[0] = x; 
			m_floats[1] = y;
			m_floats[2] = z;
			m_floats[3] = w; 
		}

		// =
		void operator = (const Vector4& v) {
			m_floats[0] = v.m_floats[0]; 
			m_floats[1] = v.m_floats[1]; 
			m_floats[2] = v.m_floats[2]; 
			m_floats[3] = v.m_floats[3];
		}
		// ==
		bool operator == (const Vector4& v) {
			return m_floats[0] == v.m_floats[0] && m_floats[1] == v.m_floats[1] && m_floats[2] == v.m_floats[2] && m_floats[3] == v.m_floats[3];
		}
		// +=
		void operator += (const Vector4& v) {
			m_floats[0] += v.m_floats[0];
			m_floats[1] += v.m_floats[1];
			m_floats[2] += v.m_floats[2];
			m_floats[3] += v.m_floats[3];
		}
		// -=
		void operator -= (const Vector4& v) {
			m_floats[0] -= v.m_floats[0];
			m_floats[1] -= v.m_floats[1];
			m_floats[2] -= v.m_floats[2];
			m_floats[3] -= v.m_floats[3];
		}
		// *=
		void operator *= (const real& k) {
			m_floats[0] *= k;
			m_floats[1] *= k;
			m_floats[2] *= k; 
			m_floats[3] *= k; 
		}
		// /=
		void operator /= (const real& k) {
			real invK = 1.0f / k; 
			m_floats[0] *= invK; 
			m_floats[1] *= invK; 
			m_floats[2] *= invK; 
			m_floats[3] *= invK;
		}

		// Friend functions
		friend Vector4 operator + (const Vector4& v1, const Vector4& v2);
		friend Vector4 operator - (const Vector4& v1, const Vector4& v2);
		friend Vector4 operator * (const Vector4& v1, const real& k);
		friend Vector4 operator / (const Vector4& v1, const real& k);
	};
};

#endif