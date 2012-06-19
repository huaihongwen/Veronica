#include "veGUI.h"

namespace vee {

	//---------------------------------------------------------------
	GUIUtility::GUIUtility() {

		// Active GUI element
		mActiveElement = NULL;
	}

	//---------------------------------------------------------------
	GUIUtility::~GUIUtility() {

	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button down
	 * @x {int} x coordinate relative to window.
	 * @y {int} y coordinate relative to window.
	 * @return {int} return flag.
	 */
	int GUIUtility::mouseLDown(int x, int y) {

		// GUI element mouseDown
		return GUI::getSingleton().getGUIElement()->mouseLDown(x, y);
	}
};