#include "veTransform.h"


namespace vee {

	//---------------------------------------------------------------
	Transform::Transform() {

		m_basic[0][0] = 1.0f; m_basic[0][1] = 0.0f; m_basic[0][2] = 0.0f; m_basic[0][3] = 0.0f;
		m_basic[1][0] = 0.0f; m_basic[1][1] = 1.0f; m_basic[1][2] = 0.0f; m_basic[1][3] = 0.0f;
		m_basic[2][0] = 0.0f; m_basic[2][1] = 0.0f; m_basic[2][2] = 1.0f; m_basic[2][3] = 0.0f;

		m_origin[0] = 0.0f; m_origin[1] = 0.0f; m_origin[2] = 0.0f; m_origin[3] = 1.0f;
	}

	//---------------------------------------------------------------
	Transform::Transform(const real& x0, const real& x1, const real& x2, const real& x3, 
		const real& y0, const real& y1, const real& y2, const real& y3, 
		const real& z0, const real& z1, const real& z2, const real& z3, 
		const real& o0, const real& o1, const real& o2, const real& o3) {

		m_basic[0][0] = x0; m_basic[0][1] = x1; m_basic[0][2] = x2; m_basic[0][3] = x3;
		m_basic[1][0] = y0; m_basic[1][1] = y1; m_basic[1][2] = y2; m_basic[1][3] = y3;
		m_basic[2][0] = z0; m_basic[2][1] = z1; m_basic[2][2] = z2; m_basic[2][3] = z3;

		m_origin[0] = o0; m_origin[1] = o1; m_origin[2] = o2; m_origin[3] = o3;
	}

	//---------------------------------------------------------------
	Transform::Transform(const Transform& m) {

		m_basic[0][0] = m.m_basic[0][0]; m_basic[0][1] = m.m_basic[0][1]; m_basic[0][2] = m.m_basic[0][2]; m_basic[0][3] = m.m_basic[0][3];
		m_basic[1][0] = m.m_basic[1][0]; m_basic[1][1] = m.m_basic[1][1]; m_basic[1][2] = m.m_basic[1][2]; m_basic[1][3] = m.m_basic[1][3];
		m_basic[2][0] = m.m_basic[2][0]; m_basic[2][1] = m.m_basic[2][1]; m_basic[2][2] = m.m_basic[2][2]; m_basic[2][3] = m.m_basic[2][3];

		m_origin[0] = m.m_origin[0]; m_origin[1] = m.m_origin[1]; m_origin[2] = m.m_origin[2]; m_origin[3] = m.m_origin[3];
	}

	//---------------------------------------------------------------
	Transform::~Transform() {
	}
	

	//---------------------------------------------------------------
	// Operator
	// =
	void Transform::operator = (const Transform& m) {

		m_basic[0][0] = m.m_basic[0][0]; m_basic[0][1] = m.m_basic[0][1]; m_basic[0][2] = m.m_basic[0][2]; m_basic[0][3] = m.m_basic[0][3];
		m_basic[1][0] = m.m_basic[1][0]; m_basic[1][1] = m.m_basic[1][1]; m_basic[1][2] = m.m_basic[1][2]; m_basic[1][3] = m.m_basic[1][3];
		m_basic[2][0] = m.m_basic[2][0]; m_basic[2][1] = m.m_basic[2][1]; m_basic[2][2] = m.m_basic[2][2]; m_basic[2][3] = m.m_basic[2][3];
		
		m_origin[0] = m.m_origin[0]; m_origin[1] = m.m_origin[1]; m_origin[2] = m.m_origin[2]; m_origin[3] = m.m_origin[3];
	}


	//---------------------------------------------------------------
	// Transform matrix * Transform matrix
	Transform operator * (const Transform& m1, const Transform& m2) {
		return Transform(
			m1.m_basic[0][0] * m2.m_basic[0][0] + m1.m_basic[1][0] * m2.m_basic[0][1] + m1.m_basic[2][0] * m2.m_basic[0][2] + m1.m_origin[0] * m2.m_basic[0][3],
			m1.m_basic[0][1] * m2.m_basic[0][0] + m1.m_basic[1][1] * m2.m_basic[0][1] + m1.m_basic[2][1] * m2.m_basic[0][2] + m1.m_origin[1] * m2.m_basic[0][3],
			m1.m_basic[0][2] * m2.m_basic[0][0] + m1.m_basic[1][2] * m2.m_basic[0][1] + m1.m_basic[2][2] * m2.m_basic[0][2] + m1.m_origin[2] * m2.m_basic[0][3],
			m1.m_basic[0][3] * m2.m_basic[0][0] + m1.m_basic[1][3] * m2.m_basic[0][1] + m1.m_basic[2][3] * m2.m_basic[0][2] + m1.m_origin[3] * m2.m_basic[0][3],

			m1.m_basic[0][0] * m2.m_basic[1][0] + m1.m_basic[1][0] * m2.m_basic[1][1] + m1.m_basic[2][0] * m2.m_basic[1][2] + m1.m_origin[0] * m2.m_basic[1][3],
			m1.m_basic[0][1] * m2.m_basic[1][0] + m1.m_basic[1][1] * m2.m_basic[1][1] + m1.m_basic[2][1] * m2.m_basic[1][2] + m1.m_origin[1] * m2.m_basic[1][3],
			m1.m_basic[0][2] * m2.m_basic[1][0] + m1.m_basic[1][2] * m2.m_basic[1][1] + m1.m_basic[2][2] * m2.m_basic[1][2] + m1.m_origin[2] * m2.m_basic[1][3],
			m1.m_basic[0][3] * m2.m_basic[1][0] + m1.m_basic[1][3] * m2.m_basic[1][1] + m1.m_basic[2][3] * m2.m_basic[1][2] + m1.m_origin[3] * m2.m_basic[1][3],

			m1.m_basic[0][0] * m2.m_basic[2][0] + m1.m_basic[1][0] * m2.m_basic[2][1] + m1.m_basic[2][0] * m2.m_basic[2][2] + m1.m_origin[0] * m2.m_basic[2][3],
			m1.m_basic[0][1] * m2.m_basic[2][0] + m1.m_basic[1][1] * m2.m_basic[2][1] + m1.m_basic[2][1] * m2.m_basic[2][2] + m1.m_origin[1] * m2.m_basic[2][3],
			m1.m_basic[0][2] * m2.m_basic[2][0] + m1.m_basic[1][2] * m2.m_basic[2][1] + m1.m_basic[2][2] * m2.m_basic[2][2] + m1.m_origin[2] * m2.m_basic[2][3],
			m1.m_basic[0][3] * m2.m_basic[2][0] + m1.m_basic[1][3] * m2.m_basic[2][1] + m1.m_basic[2][3] * m2.m_basic[2][2] + m1.m_origin[3] * m2.m_basic[2][3],

			m1.m_basic[0][0] * m2.m_origin[0] + m1.m_basic[1][0] * m2.m_origin[1] + m1.m_basic[2][0] * m2.m_origin[2] + m1.m_origin[0] * m2.m_origin[3],
			m1.m_basic[0][1] * m2.m_origin[0] + m1.m_basic[1][1] * m2.m_origin[1] + m1.m_basic[2][1] * m2.m_origin[2] + m1.m_origin[1] * m2.m_origin[3],
			m1.m_basic[0][2] * m2.m_origin[0] + m1.m_basic[1][2] * m2.m_origin[1] + m1.m_basic[2][2] * m2.m_origin[2] + m1.m_origin[2] * m2.m_origin[3],
			m1.m_basic[0][3] * m2.m_origin[0] + m1.m_basic[1][3] * m2.m_origin[1] + m1.m_basic[2][3] * m2.m_origin[2] + m1.m_origin[3] * m2.m_origin[3]
		);
	}

	//---------------------------------------------------------------
	// Transform matrix * Vector4
	Vector4 operator * (const Transform& m, const Vector4& v) {
		return Vector4(
				m.m_basic[0][0] * v[0] + m.m_basic[1][0] * v[1] + m.m_basic[2][0] * v[2] + m.m_origin[0] * v[3],
				m.m_basic[0][1] * v[0] + m.m_basic[1][1] * v[1] + m.m_basic[2][1] * v[2] + m.m_origin[1] * v[3],
				m.m_basic[0][2] * v[0] + m.m_basic[1][2] * v[1] + m.m_basic[2][2] * v[2] + m.m_origin[2] * v[3],
				m.m_basic[0][3] * v[0] + m.m_basic[1][3] * v[1] + m.m_basic[2][3] * v[2] + m.m_origin[3] * v[3]
			);
	}

	//---------------------------------------------------------------
	// Get view matrix for camera
	Transform Transform::getViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up) {
		Vector3 forwardVec = center - eye;
		Vector3 rightVec = cross(forwardVec, up);
		Vector3 upVec = cross(rightVec, forwardVec);

		rightVec.normalize();
		upVec.normalize();
		forwardVec.normalize();

		Transform rotateInverse = Transform(
			rightVec[0], upVec[0], -forwardVec[0], 0.0f,
			rightVec[1], upVec[1], -forwardVec[1], 0.0f,
			rightVec[2], upVec[2], -forwardVec[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

		Vector3 eyeInv = eye * -1.0f;
		Transform transInverse = Transform::getTranslationMatrix(eyeInv);

		return rotateInverse * transInverse;
	}

	//---------------------------------------------------------------
	// Get frustum for camera
	Transform Transform::getFrustum(const real& left, const real& right, const real& bottom, const real& top, const real& zNear, const real& zFar) {
		real nn = 2.0f * zNear;
		real rl = right - left;
		real tb = top - bottom;
		real fn = zFar - zNear;

		return Transform(
			nn / rl, 0.0f, 0.0f, 0.0f,
			0.0f, nn / tb, 0.0f, 0.0f,
			(right + left) / rl, (top + bottom) / tb, -(zFar + zNear) / fn, -1.0f,
			0.0f, 0.0f, -zFar * nn / fn, 0.0f
			);
	}

	//---------------------------------------------------------------
	// Get perspective matrix
	Transform Transform::getPerspective(const real& fovy, const real& aspect, const real& zNear, const real& zFar) {
		real top = zNear * tan(fovy * MATH_PI / 360.0f);
		real right = top * aspect;

		return Transform::getFrustum(-right, right, -top, top, zNear, zFar);
	}
};