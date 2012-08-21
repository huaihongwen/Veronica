#include "veEditor.h"

namespace vee {

	//---------------------------------------------------------------
	Editor::Editor() {

		// Engine
		// File system
		mFileSystem = NULL;

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

		// Color selection
		mColorSelector = NULL;
		// Texture panel
		//mUITexturePanel = NULL;

		// Editor
		// Scene factory
		mSceneFactory = NULL;


		// Edit data
		// Chunk
		mChunk = NULL;
		// Chunk mesh
		mMesh = NULL;
		// Factory history
		mHistory = NULL;


		// Input
		// Mouse left button area
		mMouseLArea = UI_WINDOW;

		// Mouse position
		mMousePos.x = 0;
		mMousePos.y = 0;
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


		// Edit data
		// Chunk
		mChunk = new Chunk();
		mChunk->init(16, 16, 16, 0, 0, 0);
		// Chunk mesh
		mMesh = new Mesh();
		mMesh->init(16*16*16*36);
		// Chunk history
		mHistory = new FactoryHistory();


		// Editor
		// Scene factory
		mSceneFactory = new SceneFactory();
		// Set parent pointer
		mSceneFactory->mParent = this;
		// Init scene factory
		mSceneFactory->init(mChunk, mMesh, mHistory);
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void Editor::destroy() {
		
		// Edit data
		// Chunk
		if (mChunk) {
			delete mChunk;
		}
		// Chunk mesh
		if (mMesh) {
			delete mMesh;
		}
		// Chunk history
		if (mHistory) {
			delete mHistory;
		}


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

		// File system
		mFileSystem = new veFileSystem();

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
		mTextureManager = new veTextureManager();
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

		// File system
		if (mFileSystem) {
			delete mFileSystem;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Init UI
	 */
	void Editor::_initUI() {

		// Window
		mUIWindow = new veUIComponent();
		mUIWindow->setRect(veRect(0, 0, EDITWINDOWWIDTH, EDITWINDOTHEIGHT));
		mUIWindow->setBackgroundColor(16, 16, 16);

		// Edit view
		mUIEditView = new veUIComponent();
		mUIEditView->setRect(veRect(0, 168, 800, 600));
		mUIEditView->setBackgroundColor(32, 32, 32);

		// Color selector
		mColorSelector = new veColorSelector();
		mColorSelector->setRect(veRect(820, 20, 170, 180));
		mColorSelector->setBackgroundColor(32, 32, 32);
		mColorSelector->init();

		// Texture panel
		//mUITexturePanel = new UITexturePanel();
		//mUITexturePanel->setRect(veRect(824, 268, 200, 500));
		//mUITexturePanel->setBackgroundColor(32, 32, 32);
		//mUITexturePanel->init();
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
		// Color panel
		if (mColorSelector) {
			delete mColorSelector;
		}
		// Texture panel
		//if (mUITexturePanel) {
			//delete mUITexturePanel;
		//}
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
		// Color selection
		mColorSelector->render();
		// Texture panel
		//mUITexturePanel->render();


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


		// Clicked UI_EDITVIEW
		if (mMouseLArea == UI_EDITVIEW) {

			// Scene factory mouseLDown
			mSceneFactory->mouseLDown(x, y);
		}
	}

	//---------------------------------------------------------------
	// Mouse left up
	void Editor::mouseLUp(int x, int y) {

		// UI
		_mouseLUpUI(x, y);


		// Clicked UI_EDITVIEW
		if (mMouseLArea == UI_EDITVIEW) {

			// Scene factory mouseLUp
			mSceneFactory->mouseLUp(x, y);
		}


		// Reset mouse left button area
		mMouseLArea = UI_WINDOW;
	}

	//---------------------------------------------------------------
	/**
	 * Mouse move
	 * @x {int} x coordinate after moved.
	 * @y {int} y coordinate after moved.
	 */
	void Editor::mouseMove(int x, int y) {

		// Delta
		int dx, dy;

		dx = x - mMousePos.x;
		dy = y - mMousePos.y;


		// Save new position
		mMousePos.x = x;
		mMousePos.y = y;


		// Clicked edit view
		if (mMouseLArea == UI_EDITVIEW && !mKeys[16]) {

			// Rotate camera
			mRenderer->getCamera().onCameraRotate((float)dy, (float)(-dx));

			return;
		}

		// Scene factory mouse move
		mSceneFactory->mouseMove(mMousePos.x, mMousePos.y);
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button down UI
	 */
	void Editor::_mouseLDownUI(int x, int y) {

		// Edit view
		if (mUIEditView->mouseLDown(x, y)) {
			
			mMouseLArea = UI_EDITVIEW;
		}

		// Color panel
		if (mColorSelector->mouseLDown(x, y)) {

			mMouseLArea = UI_COLORPANEL;
		}

		// Texture panel
		//if (mUITexturePanel->mouseLDown(x, y)) {
			
			//mMouseLArea = UI_TEXTUREPANEL;
		//}
	}

	//---------------------------------------------------------------
	/**
	 * Mouse left button up UI
	 */
	void Editor::_mouseLUpUI(int x, int y) {

		// Color panel
		mColorSelector->mouseLUp(x, y);

		// Texture panel
		//mUITexturePanel->mouseLUp(x, y);
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

		// File system
		veFileSystem& fs = veFileSystem::getSingleton();

		// File name buffer
		char fileName[256];


		// Scene factory key pressed
		mSceneFactory->keyPressed(key);


		// TODO: Better architect
		switch (key) {

		case '9':
			{
				// Open file dialog
				if (fs.openFileDialog(fileName)) {

					// TODO: File name validation

					// Destroy chunk
					mChunk->destroy();
					// Destroy mesh
					mMesh->destroy();
					// Destroy history
					mHistory->destroy();

					// Init chunk from file
					mChunk->init(fileName);
					// Init mesh
					mMesh->init(mChunk->mVolume.mSize[0]*mChunk->mVolume.mSize[1]*mChunk->mVolume.mSize[2]*36);

					// Destroy scene factory
					mSceneFactory->destroy();

					// Init scene factory
					mSceneFactory->init(mChunk, mMesh, mHistory);
				}
			}
			break;

		case '0':
			{
				// Save file dialog
				if (fs.saveFileDialog(fileName)) {

					// TODO: File name validation

					// Save chunk
					mChunk->saveToFile(fileName);
				}
			}
			break;

		default:
			break;
		}
	}
};