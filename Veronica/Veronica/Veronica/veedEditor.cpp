#include "veedEditor.h"

namespace veed {

	//---------------------------------------------------------------
	Editor::Editor() {

		// Engine
		// Rendering system
		mRenderSystem = NULL;
		// Renderer
		mRenderer = NULL;
		// GLSL manager
		mGLSLManager = NULL;
		// Texture manager
		mTextureManager = NULL;


		// UI
		// Window
		mUIWindow = NULL;
		// Edit view
		mUIEditView = NULL;
		// Texture panel
		mUITexturePanel = NULL;


		// Editor
		// Scene factory
		mSceneFactory = NULL;


		// Input
		// Mouse left button area
		mMouseLArea = UI_WINDOW;
	}

	//---------------------------------------------------------------
	Editor::~Editor() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void Editor::init() {

		// Engine
		_initEngine();


		// UI
		_initUI();


		// Editor
		// Scene factory
		mSceneFactory = new SceneFactory();
		mSceneFactory->initScene();
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void Editor::destroy() {
		
		// Editor
		// Scene factory
		if (mSceneFactory) {
			delete mSceneFactory;
		}


		// UI
		_destroyUI();


		// Engine
		_destroyEngine();
	}

	//---------------------------------------------------------------
	/**
	 * Update
	 */
	void Editor::update() {

		// Engine
		// Timer
		mTimer.updateFPS();
	}

	//---------------------------------------------------------------
	/**
	 * Render
	 */
	void Editor::render() {

		// Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// UI
		_renderUI();


		// Renderer
		mRenderer->render();
	}


	//---------------------------------------------------------------
	/**
	 * Init engine
	 */
	void Editor::_initEngine() {

		// Timer
		mTimer.init();

		// GLSL manager
		mGLSLManager = new GLSLManager();

		// Render system
		mRenderSystem = new RenderSystem();
		mRenderSystem->setWindowSize(EDITWINDOWWIDTH, EDITWINDOTHEIGHT);

		// Renderer
		mRenderer = new Renderer();
		// Viewport
		mRenderer->setViewport(EDITVIEWPORTX, EDITVIEWPORTY, EDITVIEWPORTWIDTH, EDITVIEWPORTHEIGHT);
		// Projection
		mRenderer->setProjection(Transform::getPerspective(45.0f, (float)EDITVIEWPORTWIDTH/(float)EDITVIEWPORTHEIGHT,
			0.1f, 1000.0f));
		mRenderer->init();

		// Texture manager
		mTextureManager = new TextureManager();
	}


	//---------------------------------------------------------------
	/**
	 * Destroy engine
	 */
	void Editor::_destroyEngine() {

		// Delete GLSL manager
		if (mGLSLManager) {
			delete mGLSLManager;
		}
		// Delete render system
		if (mRenderSystem) {
			delete mRenderSystem;
		}
		// Delete renderer
		if (mRenderer) {
			delete mRenderer;
		}
		// Delete texture manager
		if (mTextureManager) {
			delete mTextureManager;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Init UI
	 */
	void Editor::_initUI() {

		// Window
		mUIWindow = new UIComponent();
		mUIWindow->setRect(Rect(0, 0, EDITWINDOWWIDTH, EDITWINDOTHEIGHT));
		mUIWindow->setBackgroundColor(16, 16, 16);

		// Edit view
		mUIEditView = new UIComponent();
		mUIEditView->setRect(Rect(0, 168, 800, 600));
		mUIEditView->setBackgroundColor(32, 32, 32);

		// Texture panel
		mUITexturePanel = new UITexturePanel();
		mUITexturePanel->setRect(Rect(824, 268, 200, 500));
		mUITexturePanel->setBackgroundColor(32, 32, 32);
		mUITexturePanel->init();
	}

	//---------------------------------------------------------------
	/**
	 * Destroy UI
	 */
	void Editor::_destroyUI() {

		// Window
		if (mUIWindow) {
			delete mUIWindow;
		}
		// Edit view
		if (mUIEditView) {
			delete mUIEditView;
		}
		// Texture panel
		if (mUITexturePanel) {
			delete mUITexturePanel;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Render UI
	 */
	void Editor::_renderUI() {

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


		// Window
		mUIWindow->render();
		// Edit view
		mUIEditView->render();
		// Texture panel
		mUITexturePanel->render();


		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}


	//---------------------------------------------------------------
	/**
	 * Get camera
	 */
	SphericalCamera& Editor::getCamera() {
		return mRenderer->getCamera();
	}

	//---------------------------------------------------------------
	/**
	 * Get timer
	 */
	Timer* Editor::getTimer() {
		return &mTimer;
	}



	//---------------------------------------------------------------
	// TODO: Input system
	//---------------------------------------------------------------
	// Mouse left button down
	void Editor::mouseLDown(int x, int y) {

		// UI
		_mouseLDownUI(x, y);
	}

	//---------------------------------------------------------------
	// Mouse left up
	void Editor::mouseLUp(int x, int y) {

		// UI
		_mouseLUpUI(x, y);


		// Reset mouse left button area
		mMouseLArea = UI_WINDOW;
	}

	//---------------------------------------------------------------
	// Mouse move
	void Editor::mouseMove() {

		// New position
		POINT newPos;

		// Get new position
		GetCursorPos(&newPos);


		// Delta
		float dx, dy;
		dx = (float)(newPos.x - mMousePos.x);
		dy = (float)(newPos.y - mMousePos.y);


		// Save new position
		mMousePos = newPos;


		// Rotate camera
		if (mMouseLArea == UI_EDITVIEW && !mKeys[16]) {
			mRenderer->getCamera().onCameraRotate(dy, -dx);
			
			return;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button down UI
	 */
	void Editor::_mouseLDownUI(int x, int y) {

		// Edit view
		if (mUIEditView->mouseLDown(x, y)) {
			
			mMouseLArea = UI_EDITVIEW;
			return;
		}

		// Texture panel
		if (mUITexturePanel->mouseLDown(x, y)) {
			
			mMouseLArea = UI_TEXTUREPANEL;
			return;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Mouse left button up UI
	 */
	void Editor::_mouseLUpUI(int x, int y) {

		// Texture panel
		mUITexturePanel->mouseLUp(x, y);
	}


	//---------------------------------------------------------------
	// Key down
	void Editor::keyDown(WPARAM key) {
		// Key down
		mKeys[key] = false;
	}
	//---------------------------------------------------------------
	// Key up
	void Editor::keyUp(WPARAM key) {
		// Key up
		mKeys[key] = true;
	}
	//---------------------------------------------------------------
	// Key pressed
	void Editor::keyPressed(WPARAM key) {
	}
};