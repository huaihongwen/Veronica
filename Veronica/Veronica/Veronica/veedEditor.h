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
// Texture manager
#include "veTextureManager.h"


namespace veed {

	/**
	 * Mouse left button down area
	 */
	typedef enum MouseLArea {

		UI_WINDOW,

		UI_EDITVIEW,

		UI_TEXTUREPANEL

	} MouseLArea;


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
		// Texture manager
		TextureManager* mTextureManager;


	public:
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
		// Mouse left button down
		void mouseLDown(int x, int y);

		// Mouse left up
		void mouseLUp(int x, int y);

		// Mouse move
		void mouseMove();


	protected:
		/**
		 * Mouse left button down UI
		 */
		void _mouseLDownUI(int x, int y);

		/**
		 * Mouse left button up UI
		 */
		void _mouseLUpUI(int x, int y);


	public:
		// Key board
		// Key down
		void keyDown(WPARAM key);
		// Key up
		void keyUp(WPARAM key);
		// Key pressed
		void keyPressed(WPARAM key);


	protected:
		// Mouse left button area
		MouseLArea mMouseLArea;

		// Mouse position
		POINT mMousePos;


		// Key board keys
		bool mKeys[256];
	};
};

#endif