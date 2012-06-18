#include "veGUIManager.h"
#include "veRenderSystem.h"

namespace vee {

	//---------------------------------------------------------------
	GUIManager::GUIManager() {
	}

	//---------------------------------------------------------------
	GUIManager::~GUIManager() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> GUIManager* SingletonVee<GUIManager>::ms_Singleton = 0;
	GUIManager& GUIManager::getSingleton(void) {
		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	GUIManager* GUIManager::getSingletonPtr(void) {
		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/**
	 * Render GUI elements
	 */
	void GUIManager::render() {

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


		// Loop each GUI element
		for (uint i = 0; i < mGUIElements.size(); i++) {

			// Render GUI element
			mGUIElements[i]->render();
		}


		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}

	//---------------------------------------------------------------
	/**
	 * Update GUI elements
	 */
	void GUIManager::update() {

	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void GUIManager::init() {

		/*
		// Test GUI
		GUIElement* t = new GUIElement();

		// Rect
		t->setRect(Rect(0, 0, 1024, 200));

		// Color
		t->setColor(64 ,64, 64, 255);


		mGUIElements.push_back(t);
		*/
	}

	//---------------------------------------------------------------
	/**
	  * Destroy
	  */
	void GUIManager::destroy() {

		// Loop each GUI element
		for (uint i = 0; i < mGUIElements.size(); i++) {

			// Detroy GUI element
			delete mGUIElements[i];
		}

		mGUIElements.clear();
	}
};