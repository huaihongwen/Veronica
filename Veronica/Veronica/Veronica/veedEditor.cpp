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
		mLeftButton = 0;
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
	}


	//---------------------------------------------------------------
	/**
	 * Init UI
	 */
	void Editor::_initUI() {

		// Window
		mUIWindow = new UIComponent();
		mUIWindow->setRect(Rect(0, 0, EDITWINDOWWIDTH, EDITWINDOTHEIGHT));
		mUIWindow->setBackgroundColor(64, 64, 64);

		// Edit view
		mUIEditView = new UIComponent();
		mUIEditView->setRect(Rect(0, 0, 10, 10));
		mUIEditView->setBackgroundColor(128, 128, 128);

		// Texture panel
		mUITexturePanel = new UITexturePanel();
		mUITexturePanel->setRect(Rect(800, 200, 224, 468));
		mUITexturePanel->setBackgroundColor(0, 0, 0);
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































	//===============================================================
	// TODO: Input system
	//---------------------------------------------------------------
	// Mouse down
	void Editor::mouseDown(POINT& pos) {

		/*
		// Do hit test with UI components
		mLeftButton = _hitTest(pos.x, pos.y);
		

		// Dispatch mouse down event

		if (mLeftButton == UII_EDITVIEW) {

			// Scene factory
			mSceneFactory->handleMouseClick(pos.x, pos.y);
		}
		*/
	}

	//---------------------------------------------------------------
	// Mouse up
	void Editor::mouseUp() {
		
		// Reset UI index
		//mLeftButton = UII_NONE;
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
		dx = (float)(newPos.x - mMouse.x);
		dy = (float)(newPos.y - mMouse.y);


		// Save new position
		mMouse = newPos;


		// Rotate camera
		//if (mLeftButton == UII_EDITVIEW && !mKeys[16]) {

		//	mRenderer->getCamera().onCameraRotate(dy, -dx);

		//	return;
		//}


		// Dispatch mouse move event

		// Skeleton factory
		//mSkeletonFactory->handleMouseMove(dx, dy);
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

		// Dispatch key pressed event

		// Skeleton factory
		mSceneFactory->handleKeyPressed(key);
	}


	//---------------------------------------------------------------
	/*
	// UI components hit test
	int Editor::_hitTest(int px, int py) {

		// Hit test with edit view
		if (mUIEditView->hitTest(px, py)) {

			return UII_EDITVIEW;
		}

		// Hit nothing
		return UII_NONE;
	}
	*/
	//===============================================================
};