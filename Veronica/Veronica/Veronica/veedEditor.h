#ifndef VEED_EDITOR_H
#define VEED_EDITOR_H

/**
 * veedEditor.h
 */

#include "veedPrerequisites.h"
// Scene factory
#include "veedSceneFactory.h"

// UI
// Texture panel
#include "veedTexturePanel.h"


// Engine
// Timer
#include "veTimer.h"

// Render system
#include "veRenderSystem.h"
// Renderer
#include "veRenderer.h"
// GLSL manager
#include "veGLSLManager.h"


namespace veed {

	// Editor
	class Editor {

	public:
		Editor();
		~Editor();


	public:
		/**
		 * Init
		 */
		void init();

		/**
		 * Destroy
		 */
		void destroy();

		/**
		 * Update
		 */
		void update();

		/**
		 * Render
		 */
		void render();


	protected:
		/**
		 * Init engine
		 */
		void _initEngine();

		/**
		 * Destroy engine
		 */
		void _destroyEngine();


		/**
		 * Init UI
		 */
		void _initUI();

		/**
		 * Destroy UI
		 */
		void _destroyUI();

		/**
		 * Render UI
		 */
		void _renderUI();


	public:
		/**
		 * Get camera
		 */
		SphericalCamera& getCamera();

		/**
		 * Get timer
		 */
		Timer* getTimer();


	protected:
		// Engine
		// Timer
		Timer mTimer;

		// Render system
		RenderSystem* mRenderSystem;
		// Renderer
		Renderer* mRenderer;
		// GLSL manager
		GLSLManager* mGLSLManager;


		// UI
		// Window
		UIComponent* mUIWindow;
		// Edit view
		UIComponent* mUIEditView;
		// Texture panel
		UITexturePanel* mUITexturePanel;


		// Editor
		// Scene factory
		SceneFactory* mSceneFactory;

		

		//---------------------------------------------------------------
		// TODO: Input system
	public:
		// Mouse
		// Mouse down
		void mouseDown(POINT& pos);
		// Mouse up
		void mouseUp();
		// Mouse move
		void mouseMove();


		// Key board
		// Key down
		void keyDown(WPARAM key);
		// Key up
		void keyUp(WPARAM key);
		// Key pressed
		void keyPressed(WPARAM key);


	protected:
		// Mouse left button area idx
		int mLeftButton;

		// Mouse position
		POINT mMouse;


		// Key board keys
		bool mKeys[256];
	};
};

#endif