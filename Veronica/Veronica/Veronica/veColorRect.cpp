#include <math.h>
#include "veColorRect.h"
#include "veTextureManager.h"

namespace vee {
	
	// Constructor
	veColorRect::veColorRect() {}

	// Destructor
	veColorRect::~veColorRect() {}

	// Constructor
	veColorBar::veColorBar() {

		veTextureManager& tm = veTextureManager::getSingleton();

		// Ask texture manager to create and manage a new texture
		mTexture = tm.createTexture("colorbar");

		int texWidth = 8;
		int texHeight = 32;

		// Allocate memory for texture data
		uchar* texData = new uchar[texWidth * texHeight * 3];

		int idx;
		int bytesPerRow = texWidth * 3;
		
		float percent;

		for (int i = 0; i < texHeight; i++) {

			for (int j = 0; j < bytesPerRow; j += 3) {

				idx = i * texWidth * 3 + j;

				percent = (float)(i + 1) / (float)texHeight;

				CalculateSelectedColor(percent);

				texData[idx] = _mSelectedColor[0];
				texData[idx + 1] = _mSelectedColor[1];
				texData[idx + 2] = _mSelectedColor[2];
			}
		}

		mTexture->init((uint)texWidth, (uint)texHeight, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, texData);

		delete [] texData;
	}

	// Calculates the current selected color
	void veColorBar::CalculateSelectedColor(float yOffsetPerc) {

		float percentPerTransition = 1.0f / 6.0f;
		uchar valueChange;

		if (yOffsetPerc < 1.0f * percentPerTransition) {	// Red to yellow
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(255, 0 + valueChange, 0);
		}
		else if (yOffsetPerc < 2.0f * percentPerTransition) {	// Yellow to green
			yOffsetPerc -= 1.0f * percentPerTransition;
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(255 - valueChange, 255, 0);

		}
		else if (yOffsetPerc < 3.0f * percentPerTransition) {	// Green to lightblue
			yOffsetPerc -= 2.0f * percentPerTransition;
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(0, 255, 0 + valueChange);
		}
		else if (yOffsetPerc < 4.0f * percentPerTransition) {	// Lightblue to blue
			yOffsetPerc -= 3.0f * percentPerTransition;
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(0, 255 - valueChange, 255);
		}
		else if (yOffsetPerc < 5.0f * percentPerTransition) {	// Blue to purple
			yOffsetPerc -= 4.0f * percentPerTransition;
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(0 + valueChange, 0, 255);
		}
		else {											// Purple back to red
			yOffsetPerc -= 5.0f * percentPerTransition;
			yOffsetPerc /= percentPerTransition;
			valueChange = (uchar)(255 * yOffsetPerc);

			_mSelectedColor.set(255, 0, 255 - valueChange);
		}
	}

	// Destructor
	veColorBar::~veColorBar() {}
};