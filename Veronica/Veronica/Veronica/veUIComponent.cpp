#include "veUIComponent.h"
#include "veUtils.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	veUIComponent::veUIComponent() {

		// All UIs are not selected initially
		mIsSelected = false;

		mBorderWidth = 2;

		// Texture
		mTexture = NULL;
	}

	//---------------------------------------------------------------
	veUIComponent::~veUIComponent() {
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void veUIComponent::init() {}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void veUIComponent::destroy() {}

	//---------------------------------------------------------------
	/**
	 * Render
	 * This function assumes the ortho projection and viewport are
	 * already setup.
	 */
	void veUIComponent::render() {

		float x0 = float(mRect.x);
		float y0 = float(mRect.y);
		float x1 = x0 + mRect.w;
		float y1 = y0 + mRect.h;

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window height
		int wh = rs.getWindowHeight();

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
				glVertex3f(x0, wh-y1, 0.0f);
				glVertex3f(x1, wh-y1, 0.0f);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();
		}

		if (mIsSelected) {

			glLineWidth((float)mBorderWidth);
			glColor3ub(255, 255, 255);

			x0 -= mBorderWidth;
			y0 -= mBorderWidth;
			x1 += mBorderWidth;
			y1 += mBorderWidth;

			glBegin(GL_LINE_STRIP);
			glVertex3f(x0, wh-y0, 0.0f);
			glVertex3f(x0, wh-y1, 0.0f);
			glVertex3f(x1, wh-y1, 0.0f);
			glVertex3f(x1, wh-y0, 0.0f);
			glVertex3f(x0, wh-y0, 0.0f);
			glEnd();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 */
	bool veUIComponent::mouseLUp(int x, int y) {

		if (!Utils::pointInRect(vePoint(x, y), mRect)) {
			return false;
		}

		return true;
	}

	//---------------------------------------------------------------
	/**
	 * Mouse left button down
	 */
	bool veUIComponent::mouseLDown(int x, int y) {

		if (!Utils::pointInRect(vePoint(x, y), mRect)) {

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


	//---------------------------------------------------------------
	/**
	 * Set rect
	 */
	void veUIComponent::setRect(veRect& r) {
		mRect = r;
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
	void veUIComponent::setTexture(Texture* tex) {
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