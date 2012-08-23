/**
 * veUIColorRect.h
 */

#ifndef VEE_COLORRECT_H
#define VEE_COLORRECT_H

#include "vePrerequisites.h"
#include "veUIComponent.h"
#include "veColor.h"

namespace vee {

	// A color rect class, renders all intepolated colors base on a basic color
	class veColorRect : public veUIComponent {

	public:
		veColorRect();
		~veColorRect();

		// Initializeds the color rect
		void init();

		// Renders the color rect
		void render();

		// Clicks and selects color in the rect
		// Handles mouse left button down for all its sub-panels
		// @param x the x position when left button gets pressed
		// @param y the x position when left button gets pressed
		// @return true if mouse pos is inside UI rect
		bool mouseLDown(int x, int y);

		// Sets the base color of the color rect
		// @params color the ref to the new color of the base color
		void setBaseColor(veColor& color);

		// Gets x offset
		// @return the x offset of the current visual selector
		float getXOffset();

		// Gets y offset
		// @return the y offset of the current visual selector
		float getYOffset();

		// Gets the selected color as a reference
		// @return the ref to the selected color
		veColor& getSelectedColor();

		// Calculates the selected base on the offset of x, y
		// coordinates and the range of the selection
		// @param xOffset how much the x coordinate offset from the selection left
		// @param yOffset how much the y coordinate offset from the selection top
		// @param range the range of the color selection
		void calculateSelectedColor(float xOffset, float yOffset, float range);

		// Calculates and sets the texture data for the color rect.
		// Creates and init mTexture if it doesnt exist, re-upload texture's data otherwise
		void setColorRectTextureData();

	protected:
		// The current x offset from the left of the color rect
		float _mXOffset;

		// The current y offset from the top of the color rect
		float _mYOffset;

		// The current base color of this color rect
		veColor _mBaseColor;
		
		// The current selected color
		veColor _mSelectedColor;
	};
};

#endif