#ifndef VEE_MATRIX3X3_H
#define VEE_MATRIX3X3_H

/* veMatrix3x3.h
 * 3x3 column major rotation matrix
 *   Vector3		   Vector3		     Vector3
 *   m_rotates[0][0]   m_rotates[1][0]   m_rotates[2][0]
 *   m_rotates[0][1]   m_rotates[1][1]   m_rotates[2][1]
 *   m_rotates[0][2]   m_rotates[1][2]   m_rotates[2][2]
 *   m_rotates[0][w]   m_rotates[1][w]   m_rotates[2][w]
 */

#include "vePrerequisites.h"
#include "veVector3.h"

namespace vee {
	// Matrix 3x3
	class Matrix3x3 {
	public:
		// We use three Vector3 to represent a matrix3x3
		Vector3 m_rotates[3];

	public:
		Matrix3x3() { 
			m_rotates[0].setValue(1.0f, 0.0f, 0.0f);
			m_rotates[1].setValue(0.0f, 1.0f, 0.0f);
			m_rotates[2].setValue(0.0f, 0.0f, 1.0f); 
		}
		Matrix3x3(const Matrix3x3& m) { 
			m_rotates[0] = m.m_rotates[0];
			m_rotates[1] = m.m_rotates[1];
			m_rotates[2] = m.m_rotates[2]; 
		}
		Matrix3x3(const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ) { 
			m_rotates[0] = axisX; 
			m_rotates[1] = axisY;
			m_rotates[2] = axisZ; 
		}
		Matrix3x3(const real& x0, const real& x1, const real& x2,
			const real& y0, const real& y1, const real& y2, const real& z0, const real& z1, const real& z2) {

			m_rotates[0][0] = x0; m_rotates[0][1] = x1; m_rotates[0][2] = x2; 
			m_rotates[1][0] = y0; m_rotates[1][1] = y1; m_rotates[1][2] = y2;
			m_rotates[2][0] = z0; m_rotates[2][1] = z1; m_rotates[2][2] = z2;
		}

		// Get a column by index, get a vector reference
		Vector3& operator [] (int idx) { 
			return m_rotates[idx];
		}
		const Vector3& operator [] (int idx) const { 
			return m_rotates[idx];
		}
		// Get a row by index, get a vector
		Vector3 getRow(int idx) const { 
			return Vector3(m_rotates[0][idx], m_rotates[1][idx], m_rotates[2][idx]);
		}

		void setValue(const real& x0, const real& x1, const real& x2,
			const real& y0, const real& y1, const real& y2, const real& z0, const real& z1, const real& z2) {

			m_rotates[0].setValue(x0, x1, x2); 
			m_rotates[1].setValue(y0, y1, y2);
			m_rotates[2].setValue(z0, z1, z2);
		}

		// =
		void operator = (const Matrix3x3& m) { 
			m_rotates[0][0] = m.m_rotates[0][0]; m_rotates[0][1] = m.m_rotates[0][1]; m_rotates[0][2] = m.m_rotates[0][2];
			m_rotates[1][0] = m.m_rotates[1][0]; m_rotates[1][1] = m.m_rotates[1][1]; m_rotates[1][2] = m.m_rotates[1][2];
			m_rotates[2][0] = m.m_rotates[2][0]; m_rotates[2][1] = m.m_rotates[2][1]; m_rotates[2][2] = m.m_rotates[2][2];
		}
		// ==
		bool operator == (const Matrix3x3& m) { 
			return m_rotates[0] == m.m_rotates[0] && m_rotates[1] == m.m_rotates[1] && m_rotates[2] == m.m_rotates[2]; 
		}
		// +=
		void operator += (const Matrix3x3& m) {
			m_rotates[0][0] += m.m_rotates[0][0]; m_rotates[0][1] += m.m_rotates[0][1]; m_rotates[0][2] += m.m_rotates[0][2];
			m_rotates[1][0] += m.m_rotates[1][0]; m_rotates[1][1] += m.m_rotates[1][1]; m_rotates[1][2] += m.m_rotates[1][2];
			m_rotates[2][0] += m.m_rotates[2][0]; m_rotates[2][1] += m.m_rotates[2][1]; m_rotates[2][2] += m.m_rotates[2][2];
		}
		// -=
		void operator -= (const Matrix3x3& m) {
			m_rotates[0][0] -= m.m_rotates[0][0]; m_rotates[0][1] -= m.m_rotates[0][1]; m_rotates[0][2] -= m.m_rotates[0][2];
			m_rotates[1][0] -= m.m_rotates[1][0]; m_rotates[1][1] -= m.m_rotates[1][1]; m_rotates[1][2] -= m.m_rotates[1][2];
			m_rotates[2][0] -= m.m_rotates[2][0]; m_rotates[2][1] -= m.m_rotates[2][1]; m_rotates[2][2] -= m.m_rotates[2][2];
		}
		// *=
		void operator *= (const real& k) {
			m_rotates[0][0] *= k; m_rotates[0][1] *= k; m_rotates[0][2] *= k;
			m_rotates[1][0] *= k; m_rotates[1][1] *= k; m_rotates[1][2] *= k;
			m_rotates[2][0] *= k; m_rotates[2][1] *= k; m_rotates[2][2] *= k;
		}
		// /=
		void operator /= (const real& k) {
			real invK = 1.0f / k;
			m_rotates[0][0] *= invK; m_rotates[0][1] *= invK; m_rotates[0][2] *= invK;
			m_rotates[1][0] *= invK; m_rotates[1][1] *= invK; m_rotates[1][2] *= invK;
			m_rotates[2][0] *= invK; m_rotates[2][1] *= invK; m_rotates[2][2] *= invK;
		}

		// Friend functions
		friend Matrix3x3 operator + (const Matrix3x3& m1, const Matrix3x3& m2);
		friend Matrix3x3 operator - (const Matrix3x3& m1, const Matrix3x3& m2);
		friend Matrix3x3 operator * (const Matrix3x3& m, const real& k);
		friend Vector3 operator * (const Matrix3x3&, const Vector3& v);
		friend Matrix3x3 operator * (const Matrix3x3& m1, const Matrix3x3& m2 );
		friend Matrix3x3 operator / (const Matrix3x3& m, const real& k);
	};
};

#endif