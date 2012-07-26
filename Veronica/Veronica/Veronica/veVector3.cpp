#include "veVector3.h"

namespace vee {

	// Vector3
	//---------------------------------------------------------------
	// Friend +
	Vector3 operator + (const Vector3& v1, const Vector3& v2) {
		return Vector3(v1.m_floats[0] + v2.m_floats[0], v1.m_floats[1] + v2.m_floats[1], v1.m_floats[2] + v2.m_floats[2]);
	}
	//---------------------------------------------------------------
	// Friend -
	Vector3 operator - (const Vector3& v1, const Vector3& v2) {
		return Vector3(v1.m_floats[0] - v2.m_floats[0], v1.m_floats[1] - v2.m_floats[1], v1.m_floats[2] - v2.m_floats[2]);
	}
	//---------------------------------------------------------------
	// Friend *
	Vector3 operator * (const Vector3& v, const real& k) { 
		return Vector3(v.m_floats[0] * k, v.m_floats[1] * k, v.m_floats[2] * k); 
	}
	//---------------------------------------------------------------
	// Friend /
	Vector3 operator / (const Vector3& v, const real& k) { 
		real invK = 1.0f / k;
		return Vector3(v.m_floats[0] * invK, v.m_floats[1] * invK, v.m_floats[2] * invK); 
	}
	//---------------------------------------------------------------
	// Dot product
	real dot(const Vector3& v1, const Vector3& v2) { 
		return v1.m_floats[0] * v2.m_floats[0] + v1.m_floats[1] * v2.m_floats[1] + v1.m_floats[2] * v2.m_floats[2];
	}
	//---------------------------------------------------------------
	// Cross product
	Vector3 cross(const Vector3& v1, const Vector3& v2) {
		return Vector3(
			v1.m_floats[1] * v2.m_floats[2] - v2.m_floats[1] * v1.m_floats[2],
			v1.m_floats[2] * v2.m_floats[0] - v2.m_floats[2] * v1.m_floats[0],
			v1.m_floats[0] * v2.m_floats[1] - v2.m_floats[0] * v1.m_floats[1]
		);
	}


	// Vector4
	//---------------------------------------------------------------
	// Friend +
	Vector4 operator + (const Vector4& v1, const Vector4& v2) {
		return Vector4( v1.m_floats[0] + v2.m_floats[0], v1.m_floats[1] + v2.m_floats[1], v1.m_floats[2] + v2.m_floats[2], v1.m_floats[3] + v2.m_floats[3] ); 
	}
	//---------------------------------------------------------------
	// Friend -
	Vector4 operator - (const Vector4& v1, const Vector4& v2) {
		return Vector4( v1.m_floats[0] - v2.m_floats[0], v1.m_floats[1] - v2.m_floats[1], v1.m_floats[2] - v2.m_floats[2], v1.m_floats[3] - v2.m_floats[3] ); 
	}
	//---------------------------------------------------------------
	// Friend *
	Vector4 operator * (const Vector4& v, const real& k) { 
		return Vector4(v.m_floats[0] * k, v.m_floats[1] * k, v.m_floats[2] * k, v.m_floats[3] * k); 
	}
	//---------------------------------------------------------------
	// Friend /
	Vector4 operator / (const Vector4& v, const real& k) {
		real invK = 1.0f / k; return Vector4(v.m_floats[0] * invK, v.m_floats[1] * invK, v.m_floats[2] * invK, v.m_floats[3] * invK); 
	}
};