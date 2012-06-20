#ifndef VEE_GUI_H
#define VEE_GUI_H

/**
 * GUI.h
 */

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veGUIElement.h"

#include <Windows.h>

namespace vee {

	/**
	 * GUI
	 * GUI singleton, contains the GUI elements tree.
	 */
	class GUI : public SingletonVee<GUI> {

	public:
		GUI();
		~GUI();


	public:
		static GUI& getSingleton(void);
		static GUI* getSingletonPtr(void);


	public:
		/**
		 * Render
		 */
		void render();

		/**
		 * Init
		 */
		void init();

		/**
		 * Destroy
		 */
		void destroy();


	public:
		/**
		 * Get GUI element
		 */
		GUIElement* getGUIElement();


	protected:
		// Root GUI element
		GUIElement* mRoot;
	};
};

#endif