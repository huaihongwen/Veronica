#include "veColorBar.h"
//#include "veTextureManager.h"
#include "veRenderSystem.h"

namespace vee {

	veColorBar::veColorBar() {}
	veColorBar::~veColorBar() {}

	void veColorBar::init() {

		_mYOffset = 0.0f;
		calculateSelectedColor(_mYOffset, (float)_mRect.h);

		/*veTextureManager& tm = veTextureManager::getSingleton();

		// Ask texture manager to create and manage a new texture
		mTexture = tm.createTexture("colorbar");

		int texWidth = 8;
		int texHeight = 128;

		// Allocate memory for texture data
		uchar* texData = new uchar[texWidth * texHeight * 3];

		int idx;
		int bytesPerRow = texWidth * 3;

		// Write to texture data in a reverse order for OpenGL
		for (int i = texHeight - 1; i >= 0; i--) {

			calculateSelectedColor((float)(texHeight - i), (float)texHeight);

			for (int j = 0; j < bytesPerRow; j += 3) {

				idx = i * bytesPerRow + j;

				texData[idx] = _mSelectedColor[0];
				texData[idx + 1] = _mSelectedColor[1];
				texData[idx + 2] = _mSelectedColor[2];
			}
		}

		mTexture->init((uint)texWidth, (uint)texHeight, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);

		delete [] texData;*/
	}

	void veColorBar::render() {

		// Call parent's render func
		veUIComponent::render();

		float heightPerSegment = _mRect.h / 6.0f;

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Get window height
		float wh = (float)rs.getWindowHeight();

		glBegin(GL_QUADS);

		float startX = (float)_mRect.x;
		float endX = (float)(_mRect.x + _mRect.w);
		float startY = (float)_mRect.y;

		// Simple rendering logic
		// Red to purple
		glColor3ub(255, 0, 0);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(255, 0, 255);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(255, 0, 0);
		glVertex3f(endX, wh - startY, 0.0f);

		startY += heightPerSegment;

		// Purple to blue
		glColor3ub(255, 0, 255);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(0, 0, 255);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(255, 0, 255);
		glVertex3f(endX, wh - startY, 0.0f);

		startY += heightPerSegment;

		// Blue to lightblue
		glColor3ub(0, 0, 255);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(0, 255, 255);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(0, 0, 255);
		glVertex3f(endX, wh - startY, 0.0f);

		startY += heightPerSegment;

		// Lightblue to green
		glColor3ub(0, 255, 255);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(0, 255, 0);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(0, 255, 255);
		glVertex3f(endX, wh - startY, 0.0f);

		startY += heightPerSegment;

		// Green to yellow
		glColor3ub(0, 255, 0);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(255, 255, 0);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(0, 255, 0);
		glVertex3f(endX, wh - startY, 0.0f);

		startY += heightPerSegment;

		// Yellow to red
		glColor3ub(255, 255, 0);
		glVertex3f(startX, wh - startY, 0.0f);

		glColor3ub(255, 0, 0);
		glVertex3f(startX, wh - (startY + heightPerSegment), 0.0f);
		glVertex3f(endX, wh - (startY + heightPerSegment), 0.0f);

		glColor3ub(255, 255, 0);
		glVertex3f(endX, wh - startY, 0.0f);

		glEnd();

		// Draw visual selector as line
		glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex3f(startX, wh - ((float)_mRect.y + _mYOffset), 0.0f);
		glVertex3f(endX, wh - ((float)_mRect.y + _mYOffset), 0.0f);
		glEnd();
	}

	bool veColorBar::mouseLDown(int x, int y) {

		bool hitTest = veUIComponent::mouseLDown(x, y);

		if (hitTest) {
			_mYOffset = (float)y - _mRect.y;
			calculateSelectedColor(_mYOffset, (float)_mRect.h);
		}

		return hitTest;
	}

	veColor& veColorBar::getSelectedColor() {
		return _mSelectedColor;
	}

	void veColorBar::calculateSelectedColor(float yOffset, float yRange) {

		float heightPerSegment = yRange / 6.0f;
		uchar valueChange;

		if (yOffset <= 1.0f * heightPerSegment) {	// Red to purple
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255, 0, 0 + valueChange);
		}
		else if (yOffset <= 2.0f * heightPerSegment) {	// Purple to blue
			yOffset -= 1.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255 - valueChange, 0, 255);

		}
		else if (yOffset <= 3.0f * heightPerSegment) {	// Blue to lightblue
			yOffset -= 2.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0, 0 + valueChange, 255);
		}
		else if (yOffset <= 4.0f * heightPerSegment) {	// Lightblue to green
			yOffset -= 3.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0, 255, 255 - valueChange);
		}
		else if (yOffset <= 5.0f * heightPerSegment) {	// Green to yellow
			yOffset -= 4.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0 + valueChange, 255, 0);
		}
		else {											// Yellow back to red
			yOffset -= 5.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255, 255 - valueChange, 0);
		}

		//printf("Color bar's current color is %d %d %d \n", _mSelectedColor[0], _mSelectedColor[1], _mSelectedColor[2]);
	}
};