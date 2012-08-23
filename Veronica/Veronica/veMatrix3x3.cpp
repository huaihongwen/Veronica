#include "veMatrix3x3.h"

namespace vee {

	//---------------------------------------------------------------
	// Matrix + Matrix
	Matrix3x3 operator + (const Matrix3x3& m1, const Matrix3x3& m2) {
		return Matrix3x3(
			m1.m_rotates[0][0] + m2.m_rotates[0][0], m1.m_rotates[0][1] + m2.m_rotates[0][1], m1.m_rotates[0][2] + m2.m_rotates[0][2], 
			m1.m_rotates[1][0] + m2.m_rotates[1][0], m1.m_rotates[1][1] + m2.m_rotates[1][1], m1.m_rotates[1][2] + m2.m_rotates[1][2], 
			m1.m_rotates[2][0] + m2.m_rotates[2][0], m1.m_rotates[2][1] + m2.m_rotates[2][1], m1.m_rotates[2][2] + m2.m_rotates[2][2]);
	}
	//---------------------------------------------------------------
	// Matrix - Matrix
	Matrix3x3 operator - (const Matrix3x3& m1, const Matrix3x3& m2) {
		return Matrix3x3(
			m1.m_rotates[0][0] - m2.m_rotates[0][0], m1.m_rotates[0][1] - m2.m_rotates[0][1], m1.m_rotates[0][2] - m2.m_rotates[0][2], 
			m1.m_rotates[1][0] - m2.m_rotates[1][0], m1.m_rotates[1][1] - m2.m_rotates[1][1], m1.m_rotates[1][2] - m2.m_rotates[1][2], 
			m1.m_rotates[2][0] - m2.m_rotates[2][0], m1.m_rotates[2][1] - m2.m_rotates[2][1], m1.m_rotates[2][2] - m2.m_rotates[2][2]);
	}
	//---------------------------------------------------------------
	// Matrix * scalar
	Matrix3x3 operator * (const Matrix3x3& m, const real& k) {
		return Matrix3x3(
			m.m_rotates[0][0] * k, m.m_rotates[0][1] * k, m.m_rotates[0][2] * k, 
			m.m_rotates[1][0] * k, m.m_rotates[1][1] * k, m.m_rotates[1][2] * k, 
			m.m_rotates[2][0] * k, m.m_rotates[2][0] * k, m.m_rotates[2][0] * k);
	}
	//---------------------------------------------------------------
	// Matrix * vector3
	Vector3 operator * (const Matrix3x3& m, const Vector3& v) {
		return Vector3(
			m.m_rotates[0][0] * v.m_floats[0] + m.m_rotates[1][0] * v.m_floats[1] + m.m_rotates[2][0] * v.m_floats[2],
			m.m_rotates[0][1] * v.m_floats[0] + m.m_rotates[1][1] * v.m_floats[1] + m.m_rotates[2][1] * v.m_floats[2],
			m.m_rotates[0][2] * v.m_floats[0] + m.m_rotates[1][2] * v.m_floats[1] + m.m_rotates[2][2] * v.m_floats[2]);
	}
	//---------------------------------------------------------------
	// Matrix * Matrix
	Matrix3x3 operator * (const Matrix3x3& m1, const Matrix3x3& m2) {
		return Matrix3x3(	
			m1.m_rotates[0][0] * m2.m_rotates[0][0] + m1.m_rotates[1][0] * m2.m_rotates[0][1] + m1.m_rotates[2][0] * m2.m_rotates[0][2],
			m1.m_rotates[0][1] * m2.m_rotates[0][0] + m1.m_rotates[1][1] * m2.m_rotates[0][1] + m1.m_rotates[2][1] * m2.m_rotates[0][2],
			m1.m_rotates[0][2] * m2.m_rotates[0][0] + m1.m_rotates[1][2] * m2.m_rotates[0][1] + m1.m_rotates[2][2] * m2.m_rotates[0][2],
			m1.m_rotates[0][0] * m2.m_rotates[1][0] + m1.m_rotates[1][0] * m2.m_rotates[1][1] + m1.m_rotates[2][0] * m2.m_rotates[1][2],
			m1.m_rotates[0][1] * m2.m_rotates[1][0] + m1.m_rotates[1][1] * m2.m_rotates[1][1] + m1.m_rotates[2][1] * m2.m_rotates[1][2],
			m1.m_rotates[0][2] * m2.m_rotates[1][0] + m1.m_rotates[1][2] * m2.m_rotates[1][1] + m1.m_rotates[2][2] * m2.m_rotates[1][2],
			m1.m_rotates[0][0] * m2.m_rotates[2][0] + m1.m_rotates[1][0] * m2.m_rotates[2][1] + m1.m_rotates[2][0] * m2.m_rotates[2][2],
			m1.m_rotates[0][1] * m2.m_rotates[2][0] + m1.m_rotates[1][1] * m2.m_rotates[2][1] + m1.m_rotates[2][1] * m2.m_rotates[2][2],
			m1.m_rotates[0][2] * m2.m_rotates[2][0] + m1.m_rotates[1][2] * m2.m_rotates[2][1] + m1.m_rotates[2][2] * m2.m_rotates[2][2]);
	}
	//---------------------------------------------------------------
	// Matrix / scalar
	Matrix3x3 operator / (const Matrix3x3& m, const real& k) {
		real invK = 1.0f / k;
		return Matrix3x3(
			m.m_rotates[0][0] * invK, m.m_rotates[0][1] * invK, m.m_rotates[0][2] * invK, 
			m.m_rotates[1][0] * invK, m.m_rotates[1][1] * invK, m.m_rotates[1][2] * invK, 
			m.m_rotates[2][0] * invK, m.m_rotates[2][1] * invK, m.m_rotates[2][2] * invK);
	}
};