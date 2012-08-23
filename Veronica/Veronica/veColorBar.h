/**
 * veUIColorBar.h
 */

#ifndef VEE_COLORBAR_H
#define VEE_COLORBAR_H

#include "vePrerequisites.h"
#include "veUIComponent.h"
#include "veColor.h"

namespace vee {

	// A color bar class, renders all intepolated colors
	class veColorBar : public veUIComponent {

	public:
		veColorBar();
		~veColorBar();

		// Initializes the color bar
		void init();

		// Renders the color bar
		void render();

		// Clicks and selects color in the rect
		// Handles mouse left button down for all its sub-panels
		// @param x the x position when left button gets pressed
		// @param y the x position when left button gets pressed
		// @return true if mouse pos is inside UI rect
		bool mouseLDown(int x, int y);

		// Get the selected color
		veColor& getSelectedColor();

		// Calculates the current selected color for the color bar base
		// on the offset of y coordinate and the y range of the selection
		// @param yOffset how much is the y coordinate offset from the top
		// @param yRange the range of the selection in y direction
		void calculateSelectedColor(float yOffset, float yRange);

	protected:
		// The current y offset of the selected color
		float _mYOffset;
		
		// The current selected color
		veColor _mSelectedColor;
	};
};

#endif