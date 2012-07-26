#ifndef VEE_TRANSFORMCONTROLLER_H
#define VEE_TRANSFORMCONTROLLER_H


/*
 * veTransformController.h
 */


#include "vePrerequisites.h"
#include "veQuaternion.h"


namespace vee {

	// Arc render mode
	typedef enum ArcRenderMode {

		// Outline
		ARM_OUTLINE,

		// Solid
		ARM_SOLID

	} ArcRenderMode;



	// Axis index
	typedef enum AxisIndex {

		// Axis none
		AXIS_NONE,

		// Axis x
		AXIS_INDEX_X,

		// Axis y
		AXIS_INDEX_Y,

		// Axis z
		AXIS_INDEX_Z

	} AxisIndex;





































	// Transform controller
	typedef struct TransformController {

		// Base orientation
		Quaternion mBaseOrientation;

		// Base position
		Vector3 mBasePos;


		// Rotate axis
		AxisIndex mRotateAxis;

		// Rotate angle
		float mRotateAngle;

		// Rotate speed
		float mRotateSpeed;


		// Active flag
		bool mActive;


		// Bounding sphere radius
		float mBSRadius;



		//---------------------------------------------------------------
		TransformController();
		~TransformController();


		// Render
		void render();


		// Set rotate axis
		void setRotateAxis(AxisIndex axis);

		// Rotate
		void rotate(float dx, float dy);


		// Activate
		void activate();

		// Deactivate
		void deactivate();

	} TransformController;
};

#endif