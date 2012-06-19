#include "veGUI.h"
#include "veRenderSystem.h"

namespace vee {

	//---------------------------------------------------------------
	GUI::GUI() {

		// Root GUI element
		mRoot = NULL;
	}

	//---------------------------------------------------------------
	GUI::~GUI() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> GUI* SingletonVee<GUI>::ms_Singleton = 0;
	GUI& GUI::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	GUI* GUI::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/**
	 * Render
	 */
	void GUI::render() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window width
		int ww = rs.getWindowWidth();
		// Window height
		int wh = rs.getWindowHeight();


		// Ortho projection
		rs.setOrthoProjection(0.0f, (float)ww, 0.0f, (float)wh);

		// Viewport
		rs.setViewport(0, 0, ww, wh);

		// Model view identity
		rs.identityModelView();

		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);


		// Render root GUI element
		if (mRoot) {
			mRoot->render();
		}


		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void GUI::init() {

		// TODO: parse GUI layout file.



	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void GUI::destroy() {

		// Root GUI element
		if (mRoot) {
			delete mRoot;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Get GUI element
	 */
	GUIElement* GUI::getGUIElement() {

		return mRoot;
	}
};