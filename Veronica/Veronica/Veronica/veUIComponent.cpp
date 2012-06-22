#include "veUIComponent.h"
#include "veUtils.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	UIComponent::UIComponent() {

		// Texture
		mTexture = NULL;
	}

	//---------------------------------------------------------------
	UIComponent::~UIComponent() {
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void UIComponent::init() {
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void UIComponent::destroy() {
	}

	//---------------------------------------------------------------
	/**
	 * Render
	 * This function assumes the ortho projection and viewport are
	 * already setup.
	 */
	void UIComponent::render() {

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

			// Background
			glColor3ubv(mColor);

			glBegin(GL_QUADS);
				glVertex3f(x0, wh-y0, 0.0f);
				glVertex3f(x0, wh-y1, 0.0f);
				glVertex3f(x1, wh-y1, 0.0f);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 */
	void UIComponent::mouseLUp(int x, int y) {

		if (!Utils::pointInRect(Point(x, y), mRect)) {
			return;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Set rect
	 */
	void UIComponent::setRect(Rect& r) {
		mRect = r;
	}

	//---------------------------------------------------------------
	/**
	 * Set background color
	 */
	void UIComponent::setBackgroundColor(uchar r, uchar g, uchar b) {

		mColor[0] = r;
		mColor[1] = g;
		mColor[2] = b;
	}
};