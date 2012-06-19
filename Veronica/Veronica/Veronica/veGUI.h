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



	/**
	 * GUIUtility
	 * GUI utility singleton.
	 */
	class GUIUtility : public SingletonVee<GUIUtility> {

	public:
		GUIUtility();
		~GUIUtility();


	public:
		static GUIUtility& getSingleton(void);
		static GUIUtility* getSingletonPtr(void);


	public:
		/**
		 * Mouse left button down
		 */
		int mouseLDown(int x, int y);


	public:
		/**
		 * Set active element
		 */
		void setActiveElement(GUIElement* e);

		/**
		 * Get active element
		 */
		GUIElement* getActiveElement();

	protected:
		// Mouse position
		POINT mMousePos;

		// Mouse previous position
		POINT mMousePrevPos;


		// Mouse left button down pos
		POINT mMouseLDownPos;

		// Mouse left button up pos
		POINT mMouseLUpPos;

		// Mouse left button down or not
		bool mMouseLDown;


		// Keys
		bool mKeys[256];


		// Active GUI element
		GUIElement* mActiveElement;
	};
};

#endif