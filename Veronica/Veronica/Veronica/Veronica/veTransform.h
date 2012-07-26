#ifndef VEE_TRANSFORM_H
#define VEE_TRANSFORM_H


/*
 * veTransform.h
 *
 * m_basic[0][0]   m_basic[1][0]   m_basic[2][0]   m_origin[0]
 * m_basic[0][1]   m_basic[1][1]   m_basic[2][1]   m_origin[1]
 * m_basic[0][2]   m_basic[1][2]   m_basic[2][2]   m_origin[2]
 * m_basic[0][w]   m_basic[1][w]   m_basic[2][w]   m_origin[w]
 *
 */


#include "vePrerequisites.h"
// Matrix3x3
#include "veMatrix3x3.h"


namespace vee {

	// Transform matrix
	class Transform {

	public:
		// Rotation matrix
		Matrix3x3 m_basic;

		// Translate vector
		Vector3 m_origin;


	public:

		Transform();
		Transform(const real& x0, const real& x1, const real& x2, const real& x3, 
					const real& y0, const real& y1, const real& y2, const real& y3, 
					const real& z0, const real& z1, const real& z2, const real& z3, 
					const real& o0, const real& o1, const real& o2, const real& o3);
		Transform(const Transform& m);
		~Transform();


		// Operator
		// =
		void operator = (const Transform& m);


		//---------------------------------------------------------------
		// Friend operator
		friend Transform operator * (const Transform& m1, const Transform& m2);
		friend Vector4 operator * (const Transform& m, const Vector4& v);

		// Not sure
		/*
		Transform setIdentity(Transform& m) {

			m.m_basic[0][0] = 1.0f; m.m_basic[0][1] = 0.0f; m.m_basic[0][2] = 0.0f; m.m_basic[0][3] = 0.0f;
			m.m_basic[1][0] = 0.0f; m.m_basic[1][1] = 1.0f; m.m_basic[1][2] = 0.0f; m.m_basic[1][3] = 0.0f;
			m.m_basic[2][0] = 0.0f; m.m_basic[2][1] = 0.0f; m.m_basic[2][2] = 1.0f; m.m_basic[2][3] = 0.0f;
			m.m_origin[0] = 0.0f; m.m_origin[1] = 0.0f; m.m_origin[2] = 0.0f; m.m_origin[3] = 1.0f;
		}
		*/

		// Get a rotation matrix from x, y, z axises
		Transform getRotationFromAxis (const Vector3& axis_x, const Vector3& axis_y, const Vector3& axis_z) {

			Transform result = Transform();
			result.m_basic[0] = axis_x; result.m_basic[1] = axis_y; result.m_basic[2] = axis_z;

			return result;
		}

		// Get a translate matrix from translate Vector3
		static Transform getTranslationMatrix (const Vector3& deltaV) {

			Transform result = Transform();

			result.m_origin[0] = deltaV[0];
			result.m_origin[1] = deltaV[1];
			result.m_origin[2] = deltaV[2];

			// m_origin[3] is always 1.0!!!
			return result;
		}

		// Get view matrix for camera
		static Transform getViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up);

		/* getCameraFrustum
		 *@param zNear {real} // distance of the near plane along -Z direction of the camera coordinate system
		 *@param zFar {real} // distance of the far plane along -Z direction of the camera coordinate system
		 */
		static Transform getFrustum(const real& left, const real& right, 
			const real& top, const real& bottom, const real& zNear, const real& zFar);

		// Perspective projection matrix
		static Transform getPerspective(const real& fovy, const real& aspect, const real& zNear, const real& zFar);

		// toArray, for passing to rendering API
		void toArray(real* m) {
			if (!m)
				return;
			// OpenGL, column major...
			m[0] = m_basic[0][0]; m[1] = m_basic[0][1]; m[2] = m_basic[0][2]; m[3] = m_basic[0][3];
			m[4] = m_basic[1][0]; m[5] = m_basic[1][1]; m[6] = m_basic[1][2]; m[7] = m_basic[1][3];
			m[8] = m_basic[2][0]; m[9] = m_basic[2][1]; m[10] = m_basic[2][2]; m[11] = m_basic[2][3];
			m[12] = m_origin[0]; m[13] = m_origin[1]; m[14] = m_origin[2]; m[15] = m_origin[3];
		}

		// Set value
		void setValue(real* m) {
			m_basic[0][0] = m[0]; m_basic[0][1] = m[1]; m_basic[0][2] = m[2]; m_basic[0][3] = m[3];
			m_basic[1][0] = m[4]; m_basic[1][1] = m[5]; m_basic[1][2] = m[6]; m_basic[1][3] = m[7];
			m_basic[2][0] = m[8]; m_basic[2][1] = m[9]; m_basic[2][2] = m[10]; m_basic[2][3] = m[11];
			
			m_origin[0] = m[12]; m_origin[1] = m[13]; m_origin[2] = m[14]; m_origin[3] = m[15];
		}


		// Set translation
		void setTranslation(Vector3& tran) {

			m_origin[0] = tran[0];
			m_origin[1] = tran[1];
			m_origin[2] = tran[2];
		}


		/* Inverse matrix calculation
		 * @return {bool} true if we invert the matrix successfully
		 */
		bool invert() {
			// For readability
			real m[16];
			// Export data to float array
			toArray(m);

			// Determinant intermediate values array
			real inv[16];
			
			// 0-4
			inv[0]  =  m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
			inv[4]  = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
			inv[8]  =  m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
			inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];

			// 1-13
			inv[1]  = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
			inv[5]  =  m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
			inv[9]  = -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
			inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];

			// 2-14
			inv[2]  =  m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
			inv[6]  = -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
			inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
			inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];

			// 3-15
			inv[3]  = -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
			inv[7]  =  m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
			inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11] - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
			inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10] + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

			// Determinant calculation
			float det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];

			// Test if we can do the inversion
			if (det == 0) {
				return false;
			}

			// Output result matrix data to array
			det = 1.0f / det;
			for (int i = 0; i < 16; i++) {
				inv[i] *= det;
			}

			// Invert this matrix
			setValue(inv);

			return true;
		}

	};
};

#endif