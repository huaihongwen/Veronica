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
#include "veColorPalette.h"

namespace vee {

	// A basic color selector class includes 3 parts:
	//	color rect
	//	customizable color collection
	//	RGB sliders (TODO)
	class veColorSelector : public veUIComponent {

	public:
		// Constructor
		veColorSelector();
		// Destructor
		~veColorSelector();

	public:
		// Initializes the color selector
		// @params
		// @return
		void init();

		// Renders the color selector, each part seperately
		// @params
		// @return
		void render();

		// Handles mouse left button down for all its sub-panels
		// @params
		// x, y (int)		Mouse position when left button releases
		// @return
		// (bool)			Returns true if any of its sub-panels is selected
		bool mouseLDown(int x, int y);

	protected:
		veColor _mSelectedColor;		// The current selected color

		veColorRect _mColorRect;		// The color rect in this selector
		veColorBar _mColorBar;			// The color selection bar
		veColorPalette _mColorPalette;	// The customizable colors collection
	};
};

#endif