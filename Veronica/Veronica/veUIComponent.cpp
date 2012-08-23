#include "veUIComponent.h"
#include "veUtils.h"

#include <windows.h>
#include <GL\glew.h>
#include <math.h>

namespace vee {

	veUIComponent::veUIComponent() {

		// All UIs are not selected initially
		mIsSelected = false;

		mBorderWidth = 2;

		// Set default texture coordinate
		mTexCoords[0] = 0.0f;
		mTexCoords[1] = 1.0f;

		mTexCoords[2] = 0.0f;
		mTexCoords[3] = 0.0f;

		mTexCoords[4] = 1.0f;
		mTexCoords[5] = 0.0f;

		mTexCoords[6] = 1.0f;
		mTexCoords[7] = 1.0f;

		// Texture
		mTexture = NULL;
	}

	veUIComponent::~veUIComponent() {
		// TODO: delete texture using texture manager
	}

	void veUIComponent::init() {}

	void veUIComponent::destroy() {}

	void veUIComponent::render() {

		// Get the coordinates of the UI's top left and bottom right pixel pos
		float x0 = float(_mRect.x);
		float y0 = float(_mRect.y);
		float x1 = x0 + _mRect.w;
		float y1 = y0 + _mRect.h;

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();
		
		// Get window height
		int wh = rs.getWindowHeight();

		if (mIsSelected) {		// Draw a larger rect under the UI component
			glColor3ub(255, 255, 255);

			glBegin(GL_QUADS);
				glVertex3f(x0 - mBorderWidth, wh-y0 + mBorderWidth, 0.0f);
				glVertex3f(x0 - mBorderWidth, wh-y1 - mBorderWidth, 0.0f);
				glVertex3f(x1 + mBorderWidth, wh-y1 - mBorderWidth, 0.0f);
				glVertex3f(x1 + mBorderWidth, wh-y0 + mBorderWidth, 0.0f);
			glEnd();
		}

		// Texture
		if (mTexture) {
			// Bind texture
			rs.bindTexture2D(mTexture->getId(), 0);

			// Color
			glColor3ub(255, 255, 255);

			glBegin(GL_QUADS);
				glTexCoord2f(mTexCoords[0], mTexCoords[1]);
				glVertex3f(x0, wh-y0, 0.0f);

				glTexCoord2f(mTexCoords[2], mTexCoords[3]);
				glVertex3f(x0, wh-y1, 0.0f);

				glTexCoord2f(mTexCoords[4], mTexCoords[5]);
				glVertex3f(x1, wh-y1, 0.0f);

				glTexCoord2f(mTexCoords[6], mTexCoords[7]);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();

			// Unbind texture
			rs.bindTexture2D(0, 0);
		} else {

			glColor3ubv(mBgColor);

			glBegin(GL_QUADS);
				glVertex3f(x0, wh-y0, 0.0f);
				glVertex3f( x0, wh-y1, 0.0f);
				glVertex3f(x1, wh-y1, 0.0f);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 */
	bool veUIComponent::mouseLUp(int x, int y) {

		//printf("Mouse up at %d %d \n", x, y);

		if (!Utils::pointInRect(vePoint(x, y), _mRect)) {
			return false;
		}

		return true;
	}

	//---------------------------------------------------------------
	/**
	 * Mouse left button down
	 */
	bool veUIComponent::mouseLDown(int x, int y) {

		if (!Utils::pointInRect(vePoint(x, y), _mRect)) {

			if (mIsSelected) {
				mIsSelected = false;
			}

			return false;
		}

		if (!mIsSelected) {
			mIsSelected = true;
		}

		return true;
	}

	veRect& veUIComponent::getRect() {
		return _mRect;
	}

	/**
	 * Set rect
	 */
	void veUIComponent::setRect(veRect& r) {
		_mRect = r;
	}

	//---------------------------------------------------------------
	/**
	 * Set background color
	 */
	void veUIComponent::setBackgroundColor(uchar r, uchar g, uchar b) {

		mBgColor[0] = r;
		mBgColor[1] = g;
		mBgColor[2] = b;
	}

	//---------------------------------------------------------------
	/**
	 * Set texture
	 */
	void veUIComponent::setTexture(veTexture* tex) {
		mTexture = tex;
	}

	//---------------------------------------------------------------
	/**
	 * Set texture coordinates
	 */
	void veUIComponent::setTexCoords(float* coords) {
		
		for (int i = 0; i < 8; i++) {
			mTexCoords[i] = coords[i];
		}
	}
};