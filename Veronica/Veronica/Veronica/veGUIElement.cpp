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
		mType = GUI_SIMPLE;


		// Rect
		mRect = Rect(0, 0, 0,0);


		// Background color
		mBackgroundColor[0] = 0;
		mBackgroundColor[1] = 0;
		mBackgroundColor[2] = 0;
		mBackgroundColor[3] = 0;

		// Border color
		mBorderColor[0] = 0;
		mBorderColor[1] = 0;
		mBorderColor[2] = 0;
		mBorderColor[3] = 0;


		// Parent
		mParent = NULL;
	}

	//---------------------------------------------------------------
	GUIElement::~GUIElement() {

		// Destroy
		destroy();
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
	 * Render
	 * Render GUI element, this function assumes the ortho projection
	 * and viewport are already setup.
	 */
	void GUIElement::render() {

		// Four corners
		float x0 = float(mRect.x);
		float y0 = float(mRect.y);
		float x1 = x0 + mRect.w;
		float y1 = y0 + mRect.h;


		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window height
		int wh = rs.getWindowHeight();


		// Background
		glColor3ubv(mBackgroundColor);

		glBegin(GL_QUADS);
			glVertex3f(x0, wh-y0, 0.0f);
			glVertex3f(x0, wh-y1, 0.0f);
			glVertex3f(x1, wh-y1, 0.0f);
			glVertex3f(x1, wh-y0, 0.0f);
		glEnd();

		// Border
		glColor3ubv(mBorderColor);

		glBegin(GL_LINES);
			glVertex3f(x0, wh-y0, 0.0f);
			glVertex3f(x0, wh-y1, 0.0f);

			glVertex3f(x0, wh-y1, 0.0f);
			glVertex3f(x1, wh-y1, 0.0f);

			glVertex3f(x1, wh-y1, 0.0f);
			glVertex3f(x1, wh-y0, 0.0f);

			glVertex3f(x1, wh-y0, 0.0f);
			glVertex3f(x0, wh-y0, 0.0f);
		glEnd();


		// Loop each child
		for (uint i = 0; i < mChildren.size(); i++) {

			// Render child
			mChildren[i]->render();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Add child
	 * @child {GUIElement*} child pointer.
	 */
	void GUIElement::addChild(GUIElement* child) {

		mChildren.push_back(child);
	}

	//---------------------------------------------------------------
	/**
	 * Remove child
	 * @child {GUIElement*} child pointer.
	 */
	void GUIElement::removeChild(GUIElement* child) {

		uint i = 0;

		// Loop each child
		for (; i < mChildren.size(); i++) {

			if (mChildren[i] == child) {
				break;
			}
		}


		// Iterator
		vector<GUIElement*>::const_iterator c = mChildren.begin();

		if (i != mChildren.size()) {

			// Erase child
			mChildren.erase(c + i);

			// Delete child
			delete child;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Get child by type
	 * Get the first child whose type is input type.
	 * @type {GUIType} input type.
	 */
	GUIElement* GUIElement::getChildByType(GUIType type) {

		// Loop each child
		for (uint i = 0; i < mChildren.size(); i++) {

			if (mChildren[i]->getType() == type) {

				return mChildren[i];
			}
		}

		return NULL;
	}


	//---------------------------------------------------------------
	/**
	 * Set background color
	 */
	void GUIElement::setBackgroundColor(uchar r, uchar g, uchar b, uchar a) {

		mBackgroundColor[0] = r;
		mBackgroundColor[1] = g;
		mBackgroundColor[2] = b;
		mBackgroundColor[3] = a;
	}

	//---------------------------------------------------------------
	/**
	 * Set border color
	 */
	void GUIElement::setBorderColor(uchar r, uchar g, uchar b, uchar a) {

		mBorderColor[0] = r;
		mBorderColor[1] = g;
		mBorderColor[2] = b;
		mBorderColor[3] = a;
	}

	//---------------------------------------------------------------
	/**
	 * Set rect
	 */
	void GUIElement::setRect(Rect& r) {
		mRect = r;
	}

	//---------------------------------------------------------------
	/**
	 * Get type
	 * @return {GUIType} GUI element type.
	 */
	GUIType GUIElement::getType() {
		return mType;
	}
};