#include "veedTexturePanel.h"
#include "veTextureManager.h"
#include "veUtils.h"

namespace veed {

	//---------------------------------------------------------------
	UITexturePanel::UITexturePanel() {

		// Selected index
		mSelectedIdx = -1;
	}

	//---------------------------------------------------------------
	UITexturePanel::~UITexturePanel() {

		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void UITexturePanel::init() {

		// Texture manager
		TextureManager& tm = TextureManager::getSingleton();
		// Init texture
		Texture* t = tm.loadTexture("Terrain", "textures//terrain.tga");


		// Init types
		_initTypes();


		// Buttons
		// Horizontal panel margin
		int hpm = 5;
		// Vertical panel margin
		int vpm = 10;


		// Inner width
		int iw = mRect.w - hpm * 2;
		// Inner height
		int ih = mRect.h - vpm * 2;


		// Check inner space
		if (iw < 0 || ih < 0) {

			// Invalid
			return;
		}


		// Button width
		int bw = 32;
		// Button height
		int bh = 32;

		// Horizontal button margin
		int hbm = 3;
		// Vertical button margin
		int vbm = 3;


		// Acutal button width
		int abw = bw + hbm * 2;
		// Actual button height
		int abh = bh + vbm * 2;


		// Horizontal button number
		int hbNum = iw / abw;
		// Vertical button number
		int vbNum = ih / abh;


		// Horizontal space left
		int hLeft = iw - hbNum * abw;
		// Vertical space left
		int vLeft = ih - vbNum * abh;



		// Total button number
		int total = mTypes.size();

		// Button count
		int count = 0;


		// Current button
		UIComponent* b;

		// Current texture coordinates
		float coords[8];


		// Loop each row
		for (int i = 0; i < vbNum; i++) {

			// Loop each column
			for (int j = 0; j < hbNum; j++) {

				if (count == total) {

					// We already have enough button
					break;
				}


				// Curernt button
				b = new UIComponent();

				// Rect
				b->setRect(Rect(
					mRect.x + hpm + hLeft/2 + hbm + j*abw,
					mRect.y + vpm + vLeft/2 + vbm + i*abh,
					bw,
					bh));

				// Texture
				b->setTexture(t);

				// Current texture coordinates
				Utils::getVoxelFaceTexCoords(mTypes[count], 0, coords);
				b->setTexCoords(coords);


				// Push current button
				mButtons.push_back(b);

				// Increase count
				count++;
			}
		}
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void UITexturePanel::destroy() {

		// Loop each button
		for (uint i = 0; i < mButtons.size(); i++) {

			// Delete button
			delete mButtons[i];
		}

		mButtons.clear();
	}

	//---------------------------------------------------------------
	/**
	 * Render
	 */
	void UITexturePanel::render() {

		// Parent render
		UIComponent::render();


		// Loop each button
		for (uint i = 0; i < mButtons.size(); i++) {

			mButtons[i]->render();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 */
	bool UITexturePanel::mouseLUp(int x, int y) {

		// Parent mouseLUp
		if (UIComponent::mouseLUp(x, y)) {

			// Loop each button
			for (uint i = 0; i < mButtons.size(); i++) {

				if (mButtons[i]->mouseLUp(x, y)) {

					// Selected index
					mSelectedIdx = int(i);

					cout<<"Select texture:  "<<i<<endl;

					break;
				}
			}

			return true;
		} else {

			return false;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Init types
	 */
	void UITexturePanel::_initTypes() {

		// Purple brick
		mTypes.push_back(VT_PURPLEBRICK);

		// Yellow brick
		mTypes.push_back(VT_YELLOWBRICK);
	}
};