#ifndef VEED_PREREQUISITES_H
#define VEED_PREREQUISITES_H

/*
 * veedPrerequisites.h
 * This file should be included by each veed header file
 */

// Engine core stuffs
#include "vePrerequisites.h"
using namespace vee;

// Voxel model editor
namespace veed {
	
	// Debug
	#define VEED_DEBUG 1


	// Globals

	// Screen width
	#define EDITWINDOWWIDTH 1024
	// Screen height
	#define EDITWINDOTHEIGHT 768


	// Edit view port x
	#define EDITVIEWPORTX 0
	// Edit view port y
	#define EDITVIEWPORTY 0

	// Edit viewport width
	#define EDITVIEWPORTWIDTH 800
	// Edit viewport height
	#define EDITVIEWPORTHEIGHT 600


	// Pre-declare classes
	// Allows use of pointers in header files without including individual .h


	// Factory history
	class FactoryHistory;

	// Model factory
	class ModelFactory;

	// Color panel
	class UIColorPanel;

	// Editor
	class Editor;
};

#endif