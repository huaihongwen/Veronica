/**
 * veUIColorPalette.h
 */

#ifndef VEE_COLORPALETTE_H
#define VEE_COLORPALETTE_H

#include "vePrerequisites.h"
#include "veUIComponent.h"
#include "veColor.h"

namespace vee {

	// A basic customizable color palette, current supports fixed number of colors.
	// TODO: make this DIY color palette resizable and make the UI scrollable.
	class veColorPalette : public veUIComponent {

	public:
		veColorPalette();
		~veColorPalette();
	};
};

#endif