/**
 * veEditor.h
 */

#ifndef VEE_EDITOR_H
#define VEE_EDITOR_H

// Engine
#include "vePrerequisites.h"

// Timer
#include "veTimer.h"

// File system
#include "veFileSystem.h"

// Render system
#include "veRenderSystem.h"
// Renderer
#include "veRenderer.h"
// GLSL manager
#include "veGLSLManager.h"
// Texture manager
#include "veTextureManager.h"


// Editor
// Scene factory
#include "veSceneFactory.h"

// Color panel
#include "veColorSelector.h"
// Texture panel
#include "veTexturePanel.h"

namespace vee {

	/**
	 * Mouse left button down area
	 */
	typedef enum MouseLArea {

		UI_WINDOW,

		UI_EDITVIEW,

		UI_COLORPANEL,

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


	public:
		// Engine
		// Timer
		Timer mTimer;

		// File system
		veFileSystem* mFileSystem;

		// Render system
		RenderSystem* mRenderSystem;
		// Renderer
		Renderer* mRenderer;
		// GLSL manager
		GLSLManager* mGLSLManager;
		// Texture manager
		veTextureManager* mTextureManager;


	public:
		// UI
		// Window
		veUIComponent* mUIWindow;
		// Edit view
		veUIComponent* mUIEditView;
		// Color selector
		veColorSelector* mColorSelector;
		// Texture panel
		//UITexturePanel* mUITexturePanel;


		// Editor
		// Scene factory
		SceneFactory* mSceneFactory;


	public:
		// TODO: Better architect
		// Edit data
		// Chunk
		Chunk* mChunk;
		// Chunk mesh
		Mesh* mMesh;
		// Factory history
		FactoryHistory* mHistory;



		//---------------------------------------------------------------
		// TODO: Input system
	public:
		// Mouse
		// Mouse left button down
		void mouseLDown(int x, int y);

		// Mouse left up
		void mouseLUp(int x, int y);

		// Mouse move
		void mouseMove(int x, int y);


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