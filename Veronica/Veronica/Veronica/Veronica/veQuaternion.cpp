#include "veQuaternion.h"


namespace vee {

	//---------------------------------------------------------------
	// Friend *
	Quaternion operator * (const Quaternion& q, const Vector3& v) {

		Quaternion temp;
		temp.setValue(v[0], v[1], v[2]);

		return q * temp;
	}

	//---------------------------------------------------------------
	// Friend *
	Quaternion operator * (const Quaternion& qa, const Quaternion& qb) {
		
		return Quaternion(
			qa[0] * qb[3] + qa[3] * qb[0] + qa[1] * qb[2] - qa[2] * qb[1],
			qa[1] * qb[3] + qa[3] * qb[1] + qa[2] * qb[0] - qa[0] * qb[2],
			qa[2] * qb[3] + qa[3] * qb[2] + qa[0] * qb[1] - qa[1] * qb[0],
			qa[3] * qb[3] - qa[0] * qb[0] - qa[1] * qb[1] - qa[2] * qb[2]
			);
	}


	//---------------------------------------------------------------
	// Rotate point by quaternion
	Vector3 Quaternion_rotatePoint (const Quaternion& q, const Vector3& v) {

		// Inverse quaternion
		Quaternion inv = q;
		inv.invert();

		// Normalize inv
		inv.normalize();


		// q * v
		Quaternion temp = q * v;

		// temp * inv
		temp = temp * inv;

		return Vector3(temp[0], temp[1], temp[2]);
	}
};