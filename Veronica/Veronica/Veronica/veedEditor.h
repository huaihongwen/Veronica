#ifndef VEED_EDITOR_H
#define VEED_EDITOR_H

/*
 * veedEditor.h
 */

#include "veedPrerequisites.h"
// Scene factory
#include "veedSceneFactory.h"
// Color panel
#include "veedUIColorPanel.h"

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

	// UI index
	typedef enum UIIndex {

		// None
		UII_NONE,

		// Edit view
		UII_EDITVIEW,

		// Color panel
		UII_COLORPANEL

	} UIIndex;



	// Editor
	class Editor {

	public:
		Editor();
		~Editor();


	public:
		// Init
		void init();

		// Destroy
		void destroy();


		// Update
		void update();

		// Render
		void render();


	public:
		// Get camera
		SphericalCamera& getCamera();

		// Get timer
		Timer* getTimer();


	protected:
		// Initialize engine
		void _initEngine();

		// Destroy engine
		void _destroyEngine();


	//===============================================================
	// TEMP
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
		// UI components hit test
		int _hitTest(int px, int py);


	protected:
		// Mouse left button area idx
		int mLeftButton;

		// Mouse position
		POINT mMouse;


		// Key board keys
		bool mKeys[256];
	//===============================================================


	protected:
		// Engine
		//Timer
		Timer mTimer;

		// Render system
		RenderSystem* mRenderSystem;
		// Renderer
		Renderer* mRenderer;
		// GLSL manager
		GLSLManager* mGLSLManager;


		// UI components
		// Window
		UIComponent* mUIWindow;
		// Edit view
		UIComponent* mUIEditView;


		// Scene factory
		SceneFactory* mSceneFactory;
	};
};

#endif