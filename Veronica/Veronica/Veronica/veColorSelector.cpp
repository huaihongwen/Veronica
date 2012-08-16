#include "veColorSelector.h"

namespace vee {
	
	// Constructor
	veColorSelector::veColorSelector() {}

	// Destructor
	veColorSelector::~veColorSelector() {}

	// Initializes the color selector UI
	void veColorSelector::init() {
		
		_mSelectedColor.init();

		// Set the color rect base on the color selector's position, width and height
		veRect rect = veRect(mRect.x + 5, mRect.y + 5, 130, 130);
		_mColorRect.setRect(rect);
		_mColorRect.setBackgroundColor(100, 32, 32);
		_mColorRect.init();

		// Set the color bar's position, width and height
		rect.x = rect.x + rect.w + 10;
		rect.w = 20;
		_mColorBar.setRect(rect);
		_mColorBar.setBackgroundColor(32, 100, 32);
		_mColorBar.init();

		// Set the color palette's position, width and height
		rect.x = mRect.x;
		rect.y = rect.y + rect.h + 5;
		rect.w = mRect.w;
		rect.h = 35;
		_mColorPalette.setRect(rect);
		_mColorPalette.setBackgroundColor(32, 32, 100);
		_mColorPalette.init();
	}

	// Renders the color selector UI
	void veColorSelector::render() {
		
		veUIComponent::render();

		// Renders the color rect
		_mColorRect.render();
		
		// Renders the color bar
		_mColorBar.render();

		// Renders the color palette
		_mColorPalette.render();
	}

	// Handles mouse left button down
	bool veColorSelector::mouseLDown(int x, int y) {

		_mColorRect.mouseLDown(x, y);
		_mColorBar.mouseLDown(x, y);
		_mColorPalette.mouseLDown(x, y);

		return false;
	}
};