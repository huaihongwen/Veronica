#ifndef VEE_UIMANAGER_H
#define VEE_UIMANAGER_H

/* Basic UI manager
 */

#include "vePrerequisites.h"
#include "veUIComponent.h"

#include <map>

namespace vee {

	typedef map<string, UIComponent*> UIComponentMap;

	// UI manager
	class UIManager {

	public:
		UIManager() {}
		~UIManager() {}

	protected:
		// UI components
		UIComponentMap mUIComponents;
	};
};

#endif