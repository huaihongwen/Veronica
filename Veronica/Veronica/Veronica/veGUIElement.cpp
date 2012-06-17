#include "veGUIElement.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	GUIElement::GUIElement() {

		// Rect
		mRect = Rect(0, 0, 0, 0);

		// Color
		mColor[0] = 0;
		mColor[0] = 0;
		mColor[0] = 0;
		mColor[0] = 0;
	}

	//---------------------------------------------------------------
	GUIElement::~GUIElement() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Render GUI element, this function assumes the projection and viewport
	 * are setup already.
	 */
	void GUIElement::render() {

		float x0 = float(mRect.x);
		float y0 = float(mRect.y);
		float x1 = x0 + mRect.w;
		float y1 = y0 + mRect.h;


		// Render a single quad
		// Colr
		glColor3ubv(mColor);

		glBegin(GL_QUADS);
			glVertex3f(x0, y0, 0.0f);
			glVertex3f(x0, y1, 0.0f);
			glVertex3f(x1, y1, 0.0f);
			glVertex3f(x1, y0, 0.0f);
		glEnd();
	}

	//---------------------------------------------------------------
	void GUIElement::destroy() {

	}


	//---------------------------------------------------------------
	/**
	 * Set color
	 */
	void GUIElement::setColor(uchar* color) {

		mColor[0] = color[0];
		mColor[1] = color[1];
		mColor[2] = color[2];
		mColor[3] = color[3];
	}

	//---------------------------------------------------------------
	/**
	 * Set color
	 */
	void GUIElement::setColor(uchar r, uchar g, uchar b, uchar a) {

		mColor[0] = r;
		mColor[1] = g;
		mColor[2] = b;
		mColor[3] = a;
	}

	//---------------------------------------------------------------
	/**
	 * Get rect
	 */
	Rect& GUIElement::getRect() {
		return mRect;
	}

	//---------------------------------------------------------------
	/**
	 * Set rect
	 */
	void GUIElement::setRect(Rect& r) {
		mRect = r;
	}
};