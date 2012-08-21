/**
 * veUIColorSelector.h
 */

#ifndef VEE_COLORSELECTOR_H
#define VEE_COLORSELECTOR_H

#include "vePrerequisites.h"
#include "veGeometry.h"
#include "veUIComponent.h"
#include "veColor.h"
#include "veColorRect.h"
#include "veColorBar.h"
#include "veColorPalette.h"

namespace vee {

	// A basic color selector class includes serveral parts:
	// color rect
	// color bar
	// customizable color collection (TODO)
	// RGB sliders (TODO)
	class veColorSelector : public veUIComponent {

	public:
		veColorSelector();
		~veColorSelector();

	public:
		// Initializes the color selector
		void init();

		// Renders the color selector, each part seperately
		void render();

		// Handles mouse left button down for all its sub-panels
		// @param x the x position when left button gets pressed
		// @param y the x position when left button gets pressed
		// @return true if any of its sub-panels is selected
		bool mouseLDown(int x, int y);

		// Gets the selected color
		// @return the reference to the selected color
		veColor& getSelectedColor();

	protected:
		// The current selected color
		veColor _mSelectedColor;

		// The color rect in this selector
		veColorRect _mColorRect;

		// The color selection bar
		veColorBar _mColorBar;

		// The customizable colors collection
		veColorPalette _mColorPalette;
	};
};

#endif