#ifndef VEE_SPHERICALCAMERA_H
#define VEE_SPHERICALCAMERA_H

/*
----------------------------------------------------------------------
Simple camera system using spherical coordinate.
TODO: More control on camera.
----------------------------------------------------------------------
*/
#include "vePrerequisites.h"
#include "veTransform.h"

namespace vee {
	
	class SphericalCamera {
	public:
		real m_theta;				// Angle with positive Y direction
		real m_phi;					// Angle with positive Z direction
		Vector3 m_eye;

		real m_movespeed;
		real m_rotatespeed;

	public:
		SphericalCamera() { 
			m_theta = MATH_HALF_PI;
			m_phi = MATH_PI; 
			m_eye.setValue(0.0f, 0.0f, 0.0f);
			m_movespeed = 0.05f;
			m_rotatespeed = 0.002f; 
		}
		~SphericalCamera() {}

	public:
		Transform getViewMatrix() {

			real sin_theta = sin(m_theta);
			real cos_theta = cos(m_theta);
			real sin_phi = sin(m_phi);
			real cos_phi = cos(m_phi);

			Vector3 forward = Vector3(sin_theta * sin_phi, cos_theta, sin_theta * cos_phi);
		
			real upTheta = m_theta - MATH_HALF_PI;
			sin_theta = sin(upTheta);
			cos_theta = cos(upTheta);

			Vector3 up = Vector3(sin_theta * sin_phi, cos_theta, sin_theta * cos_phi);
			Transform viewMatrix = Transform::getViewMatrix(m_eye, m_eye + forward, up);

			return viewMatrix;
		}

		/**
		@params direction Boolean moving forward/backward if its true, left/right if its false
		@params add Boolean indicate the actual direction of moving
		*/
		void onCameraMove(bool direction, bool add) {
			real sin_theta = sin(m_theta);
			real cos_theta = cos(m_theta);
			real sin_phi = sin(m_phi);
			real cos_phi = cos(m_phi);

			Vector3 forward = Vector3(sin_theta * sin_phi, cos_theta, sin_theta * cos_phi);
			forward.normalize();

			real ms;
			if (add)
				ms = m_movespeed;
			else 
				ms = -m_movespeed;

			if (direction) {
				forward *= ms;
				m_eye += forward;
			}
			else {
				real upTheta = m_theta - MATH_HALF_PI;
				sin_theta = sin(upTheta);
				cos_theta = cos(upTheta);

				Vector3 up = Vector3(sin_theta * sin_phi, cos_theta, sin_theta * cos_phi);
				Vector3 right = cross(forward, up);
				right.normalize();

				right *= ms;
				m_eye += right;
			}
		}

		/**
		@params direction Boolean true for m_theta, false for m_phi
		@params theta real angle of the rotation for m_theta
		@params phi	real angle of the rotation for m_phi
		*/
		void onCameraRotate(real deltaTheta, real deltaPhi) {
			m_theta += deltaTheta * m_rotatespeed;
			m_phi += deltaPhi * m_rotatespeed;
		}
	};
};

#endif