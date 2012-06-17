#ifndef VEE_GUIMANAGER_H
#define VEE_GUIMANAGER_H

/**
 * GUI manager
 */


#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veGUIElement.h"

#include <vector>

namespace vee {

	// GUIManager
	class GUIManager : public SingletonVee<GUIManager> {

	public:
		GUIManager();
		~GUIManager();


	public:
		static GUIManager& getSingleton(void);
		static GUIManager* getSingletonPtr(void);


	public:
		/**
		 * Render GUI elements
		 */
		void render();

		/**
		 * Update GUI elements
		 */
		void update();

		
		/**
		 * Init
		 */
		void init();

		/**
		 * Destroy
		 */
		void destroy();


	protected:
		// GUI elements
		vector<GUIElement*> mGUIElements;
	};
};

#endif