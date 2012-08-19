#include <math.h>
#include "veColorRect.h"
#include "veTextureManager.h"

namespace vee {
	
	// Constructor
	veColorRect::veColorRect() {}

	// Destructor
	veColorRect::~veColorRect() {}

	// Constructor
	veColorBar::veColorBar() {}

	// Initializes the color bar
	void veColorBar::init() {

		veTextureManager& tm = veTextureManager::getSingleton();

		// Ask texture manager to create and manage a new texture
		mTexture = tm.createTexture("colorbar");

		int texWidth = 8;
		int texHeight = 32;

		// Allocate memory for texture data
		uchar* texData = new uchar[texWidth * texHeight * 3];

		int idx;
		int bytesPerRow = texWidth * 3;

		for (int i = 0; i < texHeight; i++) {

			CalculateSelectedColor((float)(i + 1), (float)texHeight);

			for (int j = 0; j < bytesPerRow; j += 3) {

				idx = i * texWidth * 3 + j;

				texData[idx] = _mSelectedColor[0];
				texData[idx + 1] = _mSelectedColor[1];
				texData[idx + 2] = _mSelectedColor[2];
			}
		}

		mTexture->init((uint)texWidth, (uint)texHeight, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);

		delete [] texData;
	}

	// Calculates the current selected color
	void veColorBar::CalculateSelectedColor(float yOffset, float yRange) {

		float heightPerSegment = yRange / 6.0f;
		uchar valueChange;

		if (yOffset <= 1.0f * heightPerSegment) {	// Red to yellow
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255, 0 + valueChange, 0);
		}
		else if (yOffset <= 2.0f * heightPerSegment) {	// Yellow to green
			yOffset -= 1.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255 - valueChange, 255, 0);

		}
		else if (yOffset <= 3.0f * heightPerSegment) {	// Green to lightblue
			yOffset -= 2.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0, 255, 0 + valueChange);
		}
		else if (yOffset <= 4.0f * heightPerSegment) {	// Lightblue to blue
			yOffset -= 3.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0, 255 - valueChange, 255);
		}
		else if (yOffset <= 5.0f * heightPerSegment) {	// Blue to purple
			yOffset -= 4.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(0 + valueChange, 0, 255);
		}
		else {											// Purple back to red
			yOffset -= 5.0f * heightPerSegment;
			valueChange = (uchar)(255 * yOffset / heightPerSegment);

			_mSelectedColor.set(255, 0, 255 - valueChange);
		}
	}

	// Destructor
	veColorBar::~veColorBar() {}
};