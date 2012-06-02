#include "veedUIColorPanel.h"
#include "veRenderSystem.h"


namespace veed {

	//---------------------------------------------------------------
	UIColorPanel::UIColorPanel() : UIComponent() {
	}

	//---------------------------------------------------------------
	UIColorPanel::UIColorPanel(string name, Rect& rect) : UIComponent(name, rect) {

		// Color bar rect
		mBar.x = mRect.x + mRect.w - 20;
		mBar.y = mRect.y;
		mBar.w = 20;
		mBar.h = mRect.h;

		// Color cube rect
		mCube.x = mRect.x;
		mCube.y = mRect.y;
		mCube.w = mRect.w - 20;
		mCube.h = mRect.h;


		// Default color bar color
		mCurrentBarColor[0] = 1.0f; mCurrentBarColor[1] = 0.0f; mCurrentBarColor[2] = 0.0f;
		
		// Default selected color
		mCurrentColor[0] = 1.0f; mCurrentColor[1] = 1.0f; mCurrentColor[2] = 1.0f;


		// Bar indicator
		mBarIndicator = 0;

		// Cube indicator
		mCubeIndicatorX = 0;
		mCubeIndicatorY = 0;
	}

	//---------------------------------------------------------------
	UIColorPanel::~UIColorPanel() {
	}

	//---------------------------------------------------------------
	// Get color
	float* UIColorPanel::getColor() {

		return mCurrentColor;
	}

	//---------------------------------------------------------------
	// Render
	void UIColorPanel::render() {

		// Prepare for rendering
		_prepare();

		// Background
		_renderBackground();

		// Color bar
		_renderBar();

		// Color cube
		_renderCube();
	}

	//---------------------------------------------------------------
	// Render color bar
	void UIColorPanel::_renderBar() {

		RenderSystem& rs = RenderSystem::getSingleton();
		// Window size
		int windowWidth = rs.getWindowWidth();
		int windowHeight = rs.getWindowHeight();

		// Upper left corner of bar
		float x = (float)mBar.x;
		float y = (float)windowHeight - mBar.y;

		// Quad size
		float quadWidth = (float)mBar.w;
		float quadHeight = mBar.h / 6.0f;


		// Color
		float RGB[3][3];
		// Red
		RGB[0][0] = 1.0f; RGB[0][1] = 0.0f; RGB[0][2] = 0.0f;
		// Green
		RGB[1][0] = 0.0f; RGB[1][1] = 1.0f; RGB[1][2] = 0.0f;
		// Blue
		RGB[2][0] = 0.0f; RGB[2][1] = 0.0f; RGB[2][2] = 1.0f;

		// Middle colro
		float middleColor[3];
		// Next color idx
		int j;


		// Render 6 quads for color bar
		glBegin(GL_QUADS);
		for (int i = 0; i < 3; i++) {

			// Next color idx
			j = i == 2 ? 0 : i+1;

			// Middle color
			middleColor[0] = RGB[i][0]; middleColor[1] = RGB[i][1]; middleColor[2] = RGB[i][2];
			middleColor[j] = 1.0f;


			// Quad 0
			glColor3fv(RGB[i]);
			glVertex3f(x, y-(i*2.0f)*quadHeight, -1.0f);
			glVertex3f(x+quadWidth, y-(i*2.0f)*quadHeight, -1.0f);

			glColor3fv(middleColor);
			glVertex3f(x+quadWidth, y-(i*2.0f+1.0f)*quadHeight, -1.0f);
			glVertex3f(x, y-(i*2.0f+1.0f)*quadHeight, -1.0f);

			// Quad 1
			glVertex3f(x, y-(i*2.0f+1.0f)*quadHeight, -1.0f);
			glVertex3f(x+quadWidth, y-(i*2.0f+1.0f)*quadHeight, -1.0f);

			glColor3fv(RGB[j]);
			glVertex3f(x+quadWidth, y-(i*2.0f+2.0f)*quadHeight, -1.0f);
			glVertex3f(x, y-(i*2.0f+2.0f)*quadHeight, -1.0f);
		}
		glEnd();


		// Render the bar color indicator
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(1.0f);
		glBegin(GL_LINES);
			glVertex3f(x, y-mBarIndicator, -1.0f);
			glVertex3f(x+quadWidth, y-mBarIndicator, -1.0f);
		glEnd();
	}


	//---------------------------------------------------------------
	// Render color cube
	void UIColorPanel::_renderCube() {

		RenderSystem& rs = RenderSystem::getSingleton();
		// Window size
		int windowWidth = rs.getWindowWidth();
		int windowHeight = rs.getWindowHeight();

		// Cube corner
		float x = (float)mCube.x;
		float y = (float)(windowHeight - mCube.y);

		// Quad size
		float quadSize = 10.0f;
		// Quad num
		int quadNum = mCube.w / 10;


		// Column color step
		float columnStep[3];
		columnStep[0] = (1.0f - mCurrentBarColor[0]) / quadNum;
		columnStep[1] = (1.0f - mCurrentBarColor[1]) / quadNum;
		columnStep[2] = (1.0f - mCurrentBarColor[2]) / quadNum;

		// Row color step
		float rowStep[3];
		// Column start color
		float columnColor[3];


		// Render quads
		glBegin(GL_QUADS);
		for (int i = 0; i < quadNum; i++) {

			// Column start color
			columnColor[0] = (1.0f - columnStep[0]*(i+1));
			columnColor[1] = (1.0f - columnStep[1]*(i+1));
			columnColor[2] = (1.0f - columnStep[2]*(i+1));

			// Row color step
			rowStep[0] = columnColor[0] / quadNum;
			rowStep[1] = columnColor[1] / quadNum;
			rowStep[2] = columnColor[2] / quadNum;

			for (int j = 0; j < quadNum; j++) {

				glColor3f(columnColor[0]-rowStep[0]*(j+1), columnColor[1]-rowStep[1]*(j+1),
					columnColor[2]-rowStep[2]*(j+1));

				glVertex3f(x+i*quadSize, y-j*quadSize, -1.0f);
				glVertex3f(x+(i+1)*quadSize, y-j*quadSize, -1.0f);
				glVertex3f(x+(i+1)*quadSize, y-(j+1)*quadSize, -1.0f);
				glVertex3f(x+i*quadSize, y-(j+1)*quadSize, -1.0f);
			}
		}
		glEnd();


		// Render cube color indicator
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(4.0f);
		glBegin(GL_POINTS);
			glVertex3f(x+mCubeIndicatorX, y-mCubeIndicatorY, -1.0f);
		glEnd();
	}


	// Handle move
	void UIColorPanel::handleMove(int dx, int dy) {

	}

	//---------------------------------------------------------------
	// Handle hit
	void UIColorPanel::_handleHit(int px, int py) {

		// Hit bar
		if (mBar.containPoint(px, py)) {

			// Save bar indicator pos y
			mBarIndicator = py - mBar.y;

			// Calculate bar color
			_calculateBarColor();
			// Calculate cube color
			_calculateCubeColor();
		}

		// Hit cube
		if (mCube.containPoint(px, py)) {

			// Save cube indicator pos x, y
			mCubeIndicatorX = px - mCube.x;
			mCubeIndicatorY = py - mCube.y;

			// Caculate cube color
			_calculateCubeColor();
		}
	}


	//---------------------------------------------------------------
	// Calculate bar color
	void UIColorPanel::_calculateBarColor() {

		// Quad height in pixel
		float quadHeight = mBar.h / 6.0f;

		// Dist in pixel
		float dist = (float)mBarIndicator;

		// Quad idx
		int idx = (int)floor(dist / quadHeight);

		// Color diff
		float colorDiff = (dist-idx*quadHeight) / quadHeight;


		switch (idx) {
		case 0:
			mCurrentBarColor[0] = 1.0f;
			mCurrentBarColor[1] = colorDiff;
			mCurrentBarColor[2] = 0.0f;
			break;

		case 1:
			mCurrentBarColor[0] = 1.0f - colorDiff;
			mCurrentBarColor[1] = 1.0f;
			mCurrentBarColor[2] = 0.0f;
			break;

		case 2:
			mCurrentBarColor[0] = 0.0f;
			mCurrentBarColor[1] = 1.0f;
			mCurrentBarColor[2] = colorDiff;
			break;

		case 3:
			mCurrentBarColor[0] = 0.0f;
			mCurrentBarColor[1] = 1.0f - colorDiff;
			mCurrentBarColor[2] = 1.0f;
			break;

		case 4:
			mCurrentBarColor[0] = colorDiff;
			mCurrentBarColor[1] = 0.0f;
			mCurrentBarColor[2] = 1.0f;
			break;

		case 5:
			mCurrentBarColor[0] = 1.0f;
			mCurrentBarColor[1] = 0.0f;
			mCurrentBarColor[2] = 1.0f - colorDiff;
			break;
		default:
			break;
		}
	}

	//---------------------------------------------------------------
	// Calculate cube color
	void UIColorPanel::_calculateCubeColor() {

		// Row percent
		float rp = (float)mCubeIndicatorX / (float)mCube.w;
		// Col percent
		float cp = (float)mCubeIndicatorY / (float)mCube.h;


		// Row diff
		float rd[3];
		rd[0] = 1.0f - mCurrentBarColor[0];
		rd[1] = 1.0f - mCurrentBarColor[1];
		rd[2] = 1.0f - mCurrentBarColor[2];

		// Row color
		float rc[3];
		rc[0] = 1.0f - rp * rd[0];
		rc[1] = 1.0f - rp * rd[1];
		rc[2] = 1.0f - rp * rd[2];


		mCurrentColor[0] = rc[0] - rc[0]*cp;
		mCurrentColor[1] = rc[1] - rc[1]*cp;
		mCurrentColor[2] = rc[2] - rc[2]*cp;
	}
};