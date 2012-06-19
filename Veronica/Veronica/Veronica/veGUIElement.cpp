#include "veGUIElement.h"
#include "veUtils.h"
#include "veRenderSystem.h"
#include "veGUI.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	GUIElement::GUIElement() {

		// GUI type
		mType = GUI_DEFAULT;


		// Rect
		mRect = Rect(0, 0, 0, 0);


		// Color
		mColor[0] = 0;
		mColor[1] = 0;
		mColor[2] = 0;
		mColor[3] = 0;

		
		// Parent GUI element
		mParent = NULL;
	}

	//---------------------------------------------------------------
	GUIElement::~GUIElement() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button down
	 * @x {int} x coordinate relative to window.
	 * @y {int} y coordinate relative to window.
	 * @return {int} return flag.
	 */
	int GUIElement::mouseLDown(int x, int y) {

		// Result
		int ret;


		// Loop each child in reverse order
		for (uint i = mChildren.size() - 1; i >= 0; i--) {

			// Handle child
			ret = mChildren[i]->mouseLDown(x, y);

			if (ret) {

				// Stop and return
				return ret;
			}
		}


		// Handle it self
		if (Utils::pointInRect(mRect, x, y)) {

			// Set it to be the active element
			GUIUtility::getSingleton().setActiveElement(this);

			return 1;

		} else {

			return 0;
		}
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


		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window height
		int wh = rs.getWindowHeight();


		// Color
		glColor3ubv(mColor);

		// Render a single quad
		glBegin(GL_QUADS);
			glVertex3f(x0, wh-y0, 0.0f);
			glVertex3f(x0, wh-y1, 0.0f);
			glVertex3f(x1, wh-y1, 0.0f);
			glVertex3f(x1, wh-y0, 0.0f);
		glEnd();


		// Loop each child
		for (uint i = 0; i < mChildren.size(); i++) {

			// Render child
			mChildren[i]->render();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void GUIElement::init() {

	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void GUIElement::destroy() {

		// Loop each child
		for (uint i = 0; i < mChildren.size(); i++) {

			// Delete child
			delete mChildren[i];
		}

		mChildren.clear();
	}


	//---------------------------------------------------------------
	/**
	 * Add child
	 */
	void GUIElement::addChild(GUIElement* child) {
		mChildren.push_back(child);
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
	 * Set rect
	 */
	void GUIElement::setRect(Rect& r) {
		mRect = r;
	}
};