#include "veColorSelector.h"

namespace vee {
	
	veColorSelector::veColorSelector() {}
	veColorSelector::~veColorSelector() {}

	void veColorSelector::init() {
		
		_mSelectedColor.init();

		// Set the color rect base on the color selector's position, width and height
		veRect rect = veRect(_mRect.x + 5, _mRect.y + 5, 130, 130);
		_mColorRect.setRect(rect);
		_mColorRect.setBackgroundColor(255, 0, 0);

		// Set the color bar's position, width and height
		rect.x = rect.x + rect.w + 10;
		rect.w = 20;
		_mColorBar.setRect(rect);
		_mColorBar.setBackgroundColor(32, 32, 32);

		// Set the color palette's position, width and height
		rect.x = _mRect.x;
		rect.y = rect.y + rect.h + 5;
		rect.w = _mRect.w;
		rect.h = 35;
		_mColorPalette.setRect(rect);
		_mColorPalette.setBackgroundColor(0, 0, 255);

		// Currently color rect has dependency on selected color of color bar
		_mColorBar.init();

		_mColorRect.setBaseColor(_mColorBar.getSelectedColor());
		_mColorRect.init();

		_mColorPalette.init();

		// Initially set selected color to the color rect's selected color
		_mSelectedColor = _mColorRect.getSelectedColor();
	}

	void veColorSelector::render() {
		
		veUIComponent::render();

		// Renders the color rect
		_mColorRect.render();
		
		// Renders the color bar
		_mColorBar.render();

		// Renders the color palette
		_mColorPalette.render();
	}

	bool veColorSelector::mouseLDown(int x, int y) {

		bool rectHitTest = _mColorRect.mouseLDown(x, y);
		bool barHitTest = _mColorBar.mouseLDown(x, y);

		if (barHitTest) {
			// TODO: this is a quick implementation to sync up color rect and
			// color bar, we should control this by event later
			_mColorRect.setBaseColor(_mColorBar.getSelectedColor());
			_mColorRect.setColorRectTextureData();

			float xoffset = _mColorRect.getXOffset();
			float yoffset = _mColorRect.getYOffset();
			veRect rect = _mColorRect.getRect();
			_mColorRect.calculateSelectedColor(xoffset, yoffset, (float)rect.h);
			
			veColor color = _mColorRect.getSelectedColor();
		}

		if (rectHitTest || barHitTest) {
			// TODO: do this by event later???
			// Sync up selector and color rect
			_mSelectedColor = _mColorRect.getSelectedColor();

			printf("Color rect's current color is %d %d %d \n", _mSelectedColor[0], _mSelectedColor[1], _mSelectedColor[2]);
		}

		bool paletteHitTest = _mColorPalette.mouseLDown(x, y);

		return (rectHitTest || barHitTest || paletteHitTest);
	}

	veColor& veColorSelector::getSelectedColor() {
		return _mSelectedColor;
	}
};