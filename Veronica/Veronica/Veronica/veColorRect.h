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

	protected:
		veColor _mBaseColor;			// The current base color of this color rect
	};

	// A color bar class, renders all intepolated colors
	class veColorBar : public veUIComponent {

	public:
		// Constructor
		veColorBar();
		// Destructor
		~veColorBar();
	};
};

#endif