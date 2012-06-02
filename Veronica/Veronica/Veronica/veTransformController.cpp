#include "veTransformController.h"

#include "veRenderer.h"
#include "veRenderSystem.h"

#include <windows.h>
#include <GL\glew.h>


namespace vee {

	//---------------------------------------------------------------
	/* Render arc
	 * Arc defined on Y-Z plane
	 *
	 * @param from {float} start radians
	 * @param to {float} end radians
	 *
	 * @param renderMode {ArcRenderMode} render mode
	 * @param color {float*} input color for rendering, rgba
	 */
	void __renderArc(float from, float to,
		ArcRenderMode renderMode, float* color) {

		// Reference segment number per loop
		int rsl = 50;


		// Total segment number for arc
		int total = int(abs(to - from) / MATH_2_PI * rsl) + 1;

		
		// Segment length in radians
		float segLen = (to - from) / total;



		// Enable blend
		glEnable(GL_BLEND);
		// Blend mode
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Color
		glColor4fv(color);


		switch (renderMode) {

		case ARM_OUTLINE:

			glBegin(GL_LINES);
			// Loop each segment
			for (int i = 0; i < total; i++) {

				glVertex3f(0.0f, float(sin(from+i*segLen)), float(cos(from+i*segLen)));
				glVertex3f(0.0f, float(sin(from+(i+1)*segLen)), float(cos(from+(i+1)*segLen)));
			}
			glEnd();

			break;

		case ARM_SOLID:

			glBegin(GL_TRIANGLES);
			// Loop each segment
			for (int i = 0; i < total; i++) {

				glVertex3f(0.0f, float(sin(from+i*segLen)), float(cos(from+i*segLen)));
				glVertex3f(0.0f, float(sin(from+(i+1)*segLen)), float(cos(from+(i+1)*segLen)));
				glVertex3f(0.0f, 0.0f, 0.0f);
			}
			glEnd();

			break;

		default:
			break;
		}


		// Disable blend
		glDisable(GL_BLEND);
	}
	


	//---------------------------------------------------------------
	/*
	 * Render axes
	 * @param orientation {Quaternion&} base orientation
	 * @param pos {Vector3&} base position
	 *
	 * @param alpha {float} input alpha for rendering
	 */
	void __renderAxes(Quaternion& orientation, Vector3& pos, float alpha=1.0f) {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Renderer
		Renderer& r = Renderer::getSingleton();


		// Model matrix
		Transform model;

		// Rotation part
		model = orientation.toMatrix();

		// Translation part
		model.setTranslation(pos);


		// View matrix
		Transform view = r.getCamera().getViewMatrix();


		
		// Set model view
		rs.setModelView(view * model);


		// Enable blend
		glEnable(GL_BLEND);
		// Blend mode
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Line width
		glLineWidth(3.0f);
		glBegin(GL_LINES);

			// X
			glColor4f(1.0f, 0.0f, 0.0f, alpha);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			// Y
			glColor4f(0.0f, 1.0f, 0.0f, alpha);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			// Z
			glColor4f(0.0f, 0.0f, 1.0f, alpha);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

		glEnd();
		glLineWidth(1.0f);


		// Disable blend
		glDisable(GL_BLEND);
	}



	//---------------------------------------------------------------
	/* Render arc on an axis
	 *
	 * @param from {float} start radians
	 * @param to {float} end radians
	 *
	 * @param orientation {Quaternion&} base orientation
	 * @param pos {Vector3&} base position
	 * @param axisIdx {AxisIndex} axis idx
	 *
	 * @param renderMode {ArcRenderMode} render mode
	 * @param color {float*} input color for rendering
	 */
	void __renderArcOnAxis(float from, float to,
		Quaternion& orientation, Vector3& pos,
		AxisIndex axisIdx,
		ArcRenderMode renderMode, float* color) {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Renderer
		Renderer& r = Renderer::getSingleton();



		// Model matrix
		Transform model;


		// View matrix
		Transform view = r.getCamera().getViewMatrix();


		// Quaternion to rotate the circle
		Quaternion q;

		switch (axisIdx) {

		case AXIS_INDEX_X:
			q.fromEulerYXZ(0.0f, 0.0f, 0.0f);
			break;

		case AXIS_INDEX_Y:
			q.fromEulerYXZ(0.0f, 0.0f, MATH_HALF_PI);
			break;

		case AXIS_INDEX_Z:
			q.fromEulerYXZ(-MATH_HALF_PI, 0.0f, 0.0f);
			break;

		default:
			return;
		}


		// Rotation
		model = (orientation * q).toMatrix();

		// Translation
		model.setTranslation(pos);



		// Set model view
		rs.setModelView(view * model);


		// Render arc
		__renderArc(from, to, renderMode, color);
	}



	//---------------------------------------------------------------
	/*
	 * Render axes circles
	 * @param orientation {Quaternion&} base orientation
	 * @param pos {Vector3&} base position
	 *
	 * @param alpha {float} input alpha for rendering
	 */
	void __renderAxesCircles(Quaternion& orientation, Vector3& pos, float alpha=1.0f) {

		// Color
		float c[4];

		// Alpha
		c[3] = alpha;


		// X
		c[0] = 1.0f;
		c[1] = 0.0f;
		c[2] = 0.0f;
		__renderArcOnAxis(0.0f, MATH_2_PI, orientation, pos, AXIS_INDEX_X, ARM_OUTLINE, c);


		// Y
		c[0] = 0.0f;
		c[1] = 1.0f;
		c[2] = 0.0f;
		__renderArcOnAxis(0.0f, MATH_2_PI, orientation, pos, AXIS_INDEX_Y, ARM_OUTLINE, c);


		// Z
		c[0] = 0.0f;
		c[1] = 0.0f;
		c[2] = 1.0f;
		__renderArcOnAxis(0.0f, MATH_2_PI, orientation, pos, AXIS_INDEX_Z, ARM_OUTLINE, c);
	}























	//---------------------------------------------------------------
	TransformController::TransformController() {

		// Base orientation
		mBaseOrientation.fromEulerYXZ(0.0f, 0.0f, 0.0f);

		// Base position
		mBasePos.setValue(0.0f, 0.0f, 0.0f);


		// Rotate axis
		mRotateAxis = AXIS_NONE;

		// Rotate angle
		mRotateAngle = 0.0f;

		// Rotate speed
		mRotateSpeed = 0.01f;


		// Active flag
		mActive = false;


		// Bounding sphere radius
		mBSRadius = 1.0f;
	}

	//---------------------------------------------------------------
	TransformController::~TransformController() {
	}


	//---------------------------------------------------------------
	void TransformController::render() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Push model view matrix
		rs.pushModelView();


		// Render axes
		__renderAxes(mBaseOrientation, mBasePos, mActive ? 1.0f : 0.25f);


		// Render axes circles
		__renderAxesCircles(mBaseOrientation, mBasePos, mActive ? 1.0f : 0.25f);



		// Render rotate angle
		float c[4];

		// RGB
		c[0] = c[1] = c[2] = 0.25f;

		// Alpha
		c[3] = 0.25f;

		__renderArcOnAxis(0.0f, -MATH_2_PI*0.7f, mBaseOrientation, mBasePos, AXIS_INDEX_X, ARM_SOLID, c);


		// Pop model view matrix
		rs.popModelView();
	}


	//---------------------------------------------------------------
	void TransformController::setRotateAxis(AxisIndex axis) {

		mRotateAxis = axis;
	}

	//---------------------------------------------------------------
	void TransformController::rotate(float dx, float dy) {

		// Set rotate angle
		
		mRotateAngle += (dx + dy) * mRotateSpeed;
	}


	//---------------------------------------------------------------
	// Activate
	void TransformController::activate() {

		mActive = true;
	}

	//---------------------------------------------------------------
	// Deactivate
	void TransformController::deactivate() {

		mActive = false;
	}
};