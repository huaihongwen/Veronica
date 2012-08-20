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
		// Constructor
		veColorRect();
		// Destructor
		~veColorRect();

		// Initializeds the color rect
		// @params
		// @return
		void init();

		// Sets the base color of the color rect
		void setBaseColor(veColor& color);

		// Calculates the current selected color for the color rect base
		// on the offset of x and y coordinates and the range of the selection
		// @params
		// xOffset (float)				How much is the x coordinate offset from the left
		// yOffset (float)				How much is the y coordinate offset from the top
		// range (float)				Range of the selection
		// @returns
		void calculateSelectedColor(float xOffset, float yOffset, float range);

		// Calculates and sets the texture data for the color rect.
		// Creates and init mTexture if it doesnt exist, reload texture's data
		// otherwise
		// @params
		// @return
		void setColorRectTextureData();

	protected:
		veColor _mBaseColor;			// The current base color of this color rect
		veColor _mSelectedColor;		// The current selected color
	};



	// A color bar class, renders all intepolated colors
	class veColorBar : public veUIComponent {

	public:
		// Constructor
		veColorBar();
		// Destructor
		~veColorBar();

		// Initializes the color bar
		// @params
		// @return
		void init();

		// Renders the color bar
		// @params
		// @return
		void render();

		// Click and select the color for color bar
		// @params
		// x, y (int)		Mouse pos when mouse down
		// @return			Returns true if its inside UI rect, false otherwise
		bool mouseLDown(int x, int y);

		// Get the selected color
		veColor& getSelectedColor();

		// Calculates the current selected color for the color bar base
		// on the offset of y coordinate and the y range of the selection
		// @params
		// yOffset (float)			How much is the y coordinate offset from the top
		// yRange (float)			Range of the selection in y direction
		// @returns
		void calculateSelectedColor(float yOffset, float yRange);

	protected:
		float _mYOffset;					// The current y offset of the selected color
		veColor _mSelectedColor;		// The current selected color
	};
};

#endif