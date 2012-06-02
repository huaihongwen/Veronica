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


		// UI components
		mUIWindow = NULL;
		mUIEditView = NULL;


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
	// Init
	void Editor::init() {

		// Engine
		_initEngine();
		
		// Timer
		mTimer.init();


		// Scene factory
		mSceneFactory = new SceneFactory();

		// Init scene
		mSceneFactory->initScene();
	}

	//---------------------------------------------------------------
	// Destroy
	void Editor::destroy() {

		// Engine
		_destroyEngine();
	}


	//---------------------------------------------------------------
	// Update
	void Editor::update() {

		// Update FPS
		mTimer.updateFPS();
	}

	//---------------------------------------------------------------
	// Render function
	void Editor::render() {

		// Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Render UI components
		// Window
		mUIWindow->render();
		// Edit view
		mUIEditView->render();


		// Renderer render
		mRenderer->render();
	}


	//---------------------------------------------------------------
	// Get camera
	SphericalCamera& Editor::getCamera() {
		return mRenderer->getCamera();
	}

	//---------------------------------------------------------------
	// Get timer
	Timer* Editor::getTimer() {
		return &mTimer;
	}


	//---------------------------------------------------------------
	// Initialize engine
	void Editor::_initEngine() {

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


		// UI components
		// Window
		mUIWindow = new UIComponent("UI_Window", Rect(0, 0, EDITWINDOWWIDTH, EDITWINDOTHEIGHT));
		mUIWindow->setBackgroundColor(0.4f, 0.4f, 0.4f);

		// Edit view
		mUIEditView = new UIComponent("UI_EditView",
			Rect(EDITVIEWPORTX, EDITWINDOTHEIGHT-EDITVIEWPORTHEIGHT, EDITVIEWPORTWIDTH, EDITVIEWPORTHEIGHT));
		mUIEditView->setBackgroundColor(0.5f, 0.5f, 0.5f);
	}

	//---------------------------------------------------------------
	// Destroy engine
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


		// UI components
		// Window
		if (mUIWindow) {
			delete mUIWindow;
		}
		// Edit view
		if (mUIEditView) {
			delete mUIEditView;
		}
	}


	//===============================================================
	// TEMP
	// TODO: Input system
	//---------------------------------------------------------------
	// Mouse down
	void Editor::mouseDown(POINT& pos) {

		// Do hit test with UI components
		mLeftButton = _hitTest(pos.x, pos.y);
		

		// Dispatch mouse down event

		if (mLeftButton == UII_EDITVIEW) {

			// Scene factory
			mSceneFactory->handleMouseClick(pos.x, pos.y);
		}
	}

	//---------------------------------------------------------------
	// Mouse up
	void Editor::mouseUp() {
		
		// Reset UI index
		mLeftButton = UII_NONE;
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
		if (mLeftButton == UII_EDITVIEW && !mKeys[16]) {

			mRenderer->getCamera().onCameraRotate(dy, -dx);

			return;
		}


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
		//mSkeletonFactory->handleKeyPressed(key);
	}


	//---------------------------------------------------------------
	// UI components hit test
	int Editor::_hitTest(int px, int py) {

		// Hit test with edit view
		if (mUIEditView->hitTest(px, py)) {

			return UII_EDITVIEW;
		}

		// Hit nothing
		return UII_NONE;
	}
	//===============================================================
};