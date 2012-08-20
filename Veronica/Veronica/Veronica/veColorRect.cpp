#include <math.h>
#include "veColorRect.h"
#include "veTextureManager.h"
#include "veRenderSystem.h"

namespace vee {
	
	// Constructor
	veColorRect::veColorRect() {}

	// Destructor
	veColorRect::~veColorRect() {}

	void veColorRect::init() {
		setColorRectTextureData();
	}

	// Sets the base color of the color rect
	void veColorRect::setBaseColor(veColor& color) {
		_mBaseColor.set(color[0], color[1], color[2], color[3]);
	}

	void veColorRect::calculateSelectedColor(float xOffset, float yOffset, float range) {
		
		// Interpolate horizontally from white to base color
		float percent = xOffset / range;
		float rDiff = (255.0f - (float)_mBaseColor[0]) * percent;
		float gDiff = (255.0f - (float)_mBaseColor[1]) * percent;
		float bDiff = (255.0f - (float)_mBaseColor[2]) * percent;

		_mSelectedColor.set((uchar)(255.0f - rDiff),
			(uchar)(255.0f - gDiff),
			(uchar)(255.0f - bDiff));

		// Interpolate vertically from result above to black
		percent = yOffset / range;
		_mSelectedColor.set((uchar)((1.0f - percent) * (float)_mSelectedColor[0]),
			(uchar)((1.0f - percent) * (float)_mSelectedColor[1]),
			(uchar)((1.0f - percent) * (float)_mSelectedColor[2]));
	}

	void veColorRect::setColorRectTextureData() {

		int texSize = 128;

		// Allocate memory for texture data
		uchar* texData = new uchar[texSize * texSize * 3];

		int idx;
		int bytesPerRow = texSize * 3;

		// Write to texture data in a reverse order for OpenGL
		for (int i = texSize - 1; i >= 0; i--) {

			for (int j = 0; j < texSize; j++) {

				idx = i * bytesPerRow + j * 3;

				calculateSelectedColor((float)(j + 1), (float)(texSize - i), (float)texSize);

				texData[idx] = _mSelectedColor[0];
				texData[idx + 1] = _mSelectedColor[1];
				texData[idx + 2] = _mSelectedColor[2];

				if ((idx + 2) == texSize * texSize * 3 - 1) {
					printf("%d %d %d\n", texData[idx], texData[idx + 1], texData[idx + 2]);
				}
			}
		}

		printf("SetColorRectTex for base color %d %d %d \n", _mBaseColor[0], _mBaseColor[1], _mBaseColor[2]);

		if (!mTexture) {
			veTextureManager& tm = veTextureManager::getSingleton();
			// Ask texture manager to create and manage a new texture
			mTexture = tm.createTexture("colorrect");

			mTexture->init((uint)texSize, (uint)texSize, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);
		}
		else {
			mTexture->reload((uint)texSize, (uint)texSize, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);
		}

		delete [] texData;
	}

	// Constructor
	veColorBar::veColorBar() {}

	// Destructor
	veColorBar::~veColorBar() {}

	// Initializes the color bar
	void veColorBar::init() {

		_mYOffset = 0.0f;
		calculateSelectedColor(_mYOffset, (float)mRect.h);

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

	// Renders the color bar
	void veColorBar::render() {

		// Call parent's render func
		veUIComponent::render();

		float heightPerSegment = mRect.h / 6.0f;

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Get window height
		float wh = (float)rs.getWindowHeight();

		glBegin(GL_QUADS);

		float startX = (float)mRect.x;
		float endX = (float)(mRect.x + mRect.w);
		float startY = (float)mRect.y;

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
		glVertex3f(startX, wh - ((float)mRect.y + _mYOffset), 0.0f);
		glVertex3f(endX, wh - ((float)mRect.y + _mYOffset), 0.0f);
		glEnd();
	}

	// CLick and select the color for color bar
	bool veColorBar::mouseLDown(int x, int y) {

		bool hitTest = veUIComponent::mouseLDown(x, y);

		if (hitTest) {
			_mYOffset = (float)y - mRect.y;
			calculateSelectedColor(_mYOffset, (float)mRect.h);
		}

		return hitTest;
	}

	veColor& veColorBar::getSelectedColor() {
		return _mSelectedColor;
	}

	// Calculates the current selected color
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