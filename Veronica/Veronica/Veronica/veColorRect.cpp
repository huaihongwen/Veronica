#include <math.h>
#include "veColorRect.h"
#include "veTextureManager.h"
#include "veRenderSystem.h"

namespace vee {
	
	veColorRect::veColorRect() {}
	veColorRect::~veColorRect() {}

	void veColorRect::init() {
		setColorRectTextureData();

		_mXOffset = 0.0f;
		_mYOffset = 0.0f;

		calculateSelectedColor(_mXOffset, _mYOffset, (float)_mRect.h);
	}

	void veColorRect::render(){

		// Call render on parent class
		veUIComponent::render();

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Get window height
		float wh = (float)rs.getWindowHeight();

		glColor3ub(255, 0, 0);
		glPointSize(3.0f);

		glBegin(GL_POINTS);
		glVertex3f((float)(_mRect.x + _mXOffset), (float)(wh - _mRect.y - _mYOffset), 0.0f);
		glEnd();
	}

	bool veColorRect::mouseLDown(int x, int y) {

		bool hitTest = veUIComponent::mouseLDown(x, y);

		if (hitTest) {
			_mXOffset = (float)x - _mRect.x;
			_mYOffset = (float)y - _mRect.y;

			calculateSelectedColor(_mXOffset, _mYOffset, (float)_mRect.h);
		}

		return hitTest;
	}

	void veColorRect::setBaseColor(veColor& color) {
		_mBaseColor.set(color[0], color[1], color[2], color[3]);
	}

	float veColorRect::getXOffset() {
		return _mXOffset;
	}

	float veColorRect::getYOffset() {
		return _mYOffset;
	}

	veColor& veColorRect::getSelectedColor() {
		return _mSelectedColor;
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
			}
		}

		if (!mTexture) {
			veTextureManager& tm = veTextureManager::getSingleton();
			// Ask texture manager to create and manage a new texture
			mTexture = tm.createTexture("colorrect");

			mTexture->init((uint)texSize, (uint)texSize, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);
		}
		else {
			mTexture->reUpload(0, 0, (uint)texSize, (uint)texSize, GL_RGB, GL_UNSIGNED_BYTE, texData);
		}

		delete [] texData;
	}

};