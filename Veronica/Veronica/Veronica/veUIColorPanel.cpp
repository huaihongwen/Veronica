#include "veUIColorPanel.h"
#include "veRenderSystem.h"
#include "veUtils.h"

namespace vee {

	//---------------------------------------------------------------
	UIColorPanel::UIColorPanel() {
	}

	//---------------------------------------------------------------
	UIColorPanel::~UIColorPanel() {
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void UIColorPanel::init() {

		// Bar width
		int bw = 20;


		// Horizontal panel margin
		int hpm = 15;
		// Vertical panel margin
		int vpm = 15;


		// Inner width
		int iw = mRect.w - hpm*2;
		// Inner height
		int ih = mRect.h - vpm*2;


		// Check inner space
		if (iw < bw || ih < 0) {

			// Invalid
			return;
		}


		// Bar rect
		mBarRect.x = mRect.x + hpm + iw - bw;
		mBarRect.y = mRect.y + vpm;
		mBarRect.w = bw;
		mBarRect.h = ih;


		// Cube rect
		mCubeRect.x = mRect.x + hpm;
		mCubeRect.y = mRect.y + vpm;
		mCubeRect.w = iw - bw;
		mCubeRect.h = ih;


		// Bar color
		mBarColor[0] = 1.0f;
		mBarColor[1] = 0.0f;
		mBarColor[2] = 0.0f;

		// Cube color
		mCubeColor[0] = 0.0f;
		mCubeColor[1] = 0.0f;
		mCubeColor[2] = 0.0f;


		// Bar indicator pos y
		mBarIndicator = 0;

		
		// Cube indicator pos x
		mCubeIndicatorX = 0;
		// Cube indicator pos y
		mCubeIndicatorY = 0;
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void UIColorPanel::destroy() {

	}

	//---------------------------------------------------------------
	/**
	 * Render
	 */
	void UIColorPanel::render() {

		// Parent render
		UIComponent::render();


		// Render bar
		_renderBar();


		// Render cube
		_renderCube();
	}


	//---------------------------------------------------------------
	/**
	 * Mouse left button up
	 */
	bool UIColorPanel::mouseLUp(int x, int y) {

		// Parent mouseLUp
		if (UIComponent::mouseLUp(x, y)) {

			// Select color
			_selectColor(x, y);

			return true;
		} else {

			return false;
		}
	}


	//---------------------------------------------------------------
	/**
	 * Render bar
	 */
	void UIColorPanel::_renderBar() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window height
		int wh = rs.getWindowHeight();


		// Bar corner
		float x = (float)mBarRect.x;
		float y = (float)wh - mBarRect.y;


		// Quad width
		float qw = (float)mBarRect.w;
		// Quad height
		float qh = mBarRect.h / 6.0f;


		// Color
		float RGB[3][3];
		// Red
		RGB[0][0] = 1.0f; RGB[0][1] = 0.0f; RGB[0][2] = 0.0f;
		// Green
		RGB[1][0] = 0.0f; RGB[1][1] = 1.0f; RGB[1][2] = 0.0f;
		// Blue
		RGB[2][0] = 0.0f; RGB[2][1] = 0.0f; RGB[2][2] = 1.0f;


		// Middle color
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
			glVertex3f(x, y-(i*2.0f)*qh, 0.0f);
			glVertex3f(x+qw, y-(i*2.0f)*qh, 0.0f);

			glColor3fv(middleColor);
			glVertex3f(x+qw, y-(i*2.0f+1.0f)*qh, 0.0f);
			glVertex3f(x, y-(i*2.0f+1.0f)*qh, 0.0f);

			// Quad 1
			glVertex3f(x, y-(i*2.0f+1.0f)*qh, 0.0f);
			glVertex3f(x+qw, y-(i*2.0f+1.0f)*qh, 0.0f);

			glColor3fv(RGB[j]);
			glVertex3f(x+qw, y-(i*2.0f+2.0f)*qh, 0.0f);
			glVertex3f(x, y-(i*2.0f+2.0f)*qh, 0.0f);
		}

		glEnd();
		

		// Render the bar color indicator
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(1.0f);

		glBegin(GL_LINES);
			glVertex3f(x, y-mBarIndicator, 0.0f);
			glVertex3f(x+qw, y-mBarIndicator, 0.0f);
		glEnd();
	}

	//---------------------------------------------------------------
	/**
	 * Render cube
	 */
	void UIColorPanel::_renderCube() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Window height
		int wh = rs.getWindowHeight();


		// Cube corner
		float x = (float)mCubeRect.x;
		float y = (float)(wh - mCubeRect.y);


		// Quad number
		int qNum = 25;

		// Quad width
		float qw = (float)mCubeRect.w / qNum;
		// Quad height
		float qh = (float)mCubeRect.h / qNum;


		// Column color step
		float columnStep[3];
		columnStep[0] = (1.0f - mBarColor[0]) / qNum;
		columnStep[1] = (1.0f - mBarColor[1]) / qNum;
		columnStep[2] = (1.0f - mBarColor[2]) / qNum;

		// Row color step
		float rowStep[3];
		// Column start color
		float columnColor[3];


		// Render quads
		glBegin(GL_QUADS);

		for (int i = 0; i < qNum; i++) {

			// Column start color
			columnColor[0] = (1.0f - columnStep[0]*(i+1));
			columnColor[1] = (1.0f - columnStep[1]*(i+1));
			columnColor[2] = (1.0f - columnStep[2]*(i+1));

			// Row color step
			rowStep[0] = columnColor[0] / qNum;
			rowStep[1] = columnColor[1] / qNum;
			rowStep[2] = columnColor[2] / qNum;

			for (int j = 0; j < qNum; j++) {

				glColor3f(columnColor[0]-rowStep[0]*(j+1), columnColor[1]-rowStep[1]*(j+1),
					columnColor[2]-rowStep[2]*(j+1));

				glVertex3f(x+i*qw, y-j*qh, 0.0f);
				glVertex3f(x+(i+1)*qw, y-j*qh, 0.0f);
				glVertex3f(x+(i+1)*qw, y-(j+1)*qh, 0.0f);
				glVertex3f(x+i*qw, y-(j+1)*qh, 0.0f);
			}
		}

		glEnd();


		// Render cube color indicator
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(4.0f);
		
		glBegin(GL_POINTS);
			glVertex3f(x+mCubeIndicatorX, y-mCubeIndicatorY, 0.0f);
		glEnd();
	}


	//---------------------------------------------------------------
	/**
	 *
	 */
	void UIColorPanel::_selectColor(int x, int y) {

		// Bar
		if (Utils::pointInRect(Point(x, y), mBarRect)) {

			// Bar indicator pos y
			mBarIndicator = y - mBarRect.y;

			
			// Calculates bar color
			_calculateBarColor();

			// Calculates cube color
			_calculateCubeColor();
		}

		// Cube
		if (Utils::pointInRect(Point(x, y), mCubeRect)) {

			// Cube indicator x
			mCubeIndicatorX = x - mCubeRect.x;
			// Cube indicator y
			mCubeIndicatorY = y - mCubeRect.y;
			

			// Caculates cube color
			_calculateCubeColor();
		}
	}


	//---------------------------------------------------------------
	/**
	 * Calculates bar color
	 */
	void UIColorPanel::_calculateBarColor() {

		// Quad height
		float qh = mBarRect.h / 6.0f;

		// Dist
		float dist = (float)mBarIndicator;

		// Quad idx
		int idx = (int)floor(dist / qh);

		// Color diff
		float colorDiff = (dist-idx*qh) / qh;


		switch (idx) {
		case 0:
			mBarColor[0] = 1.0f;
			mBarColor[1] = colorDiff;
			mBarColor[2] = 0.0f;
			break;

		case 1:
			mBarColor[0] = 1.0f - colorDiff;
			mBarColor[1] = 1.0f;
			mBarColor[2] = 0.0f;
			break;

		case 2:
			mBarColor[0] = 0.0f;
			mBarColor[1] = 1.0f;
			mBarColor[2] = colorDiff;
			break;

		case 3:
			mBarColor[0] = 0.0f;
			mBarColor[1] = 1.0f - colorDiff;
			mBarColor[2] = 1.0f;
			break;

		case 4:
			mBarColor[0] = colorDiff;
			mBarColor[1] = 0.0f;
			mBarColor[2] = 1.0f;
			break;

		case 5:
			mBarColor[0] = 1.0f;
			mBarColor[1] = 0.0f;
			mBarColor[2] = 1.0f - colorDiff;
			break;

		default:
			break;
		}
	}

	//---------------------------------------------------------------
	/**
	 * Calculates cube color
	 */
	void UIColorPanel::_calculateCubeColor() {

		// Row percent
		float rp = (float)mCubeIndicatorX / (float)mCubeRect.w;
		// Col percent
		float cp = (float)mCubeIndicatorY / (float)mCubeRect.h;


		// Row diff
		float rd[3];
		rd[0] = 1.0f - mBarColor[0];
		rd[1] = 1.0f - mBarColor[1];
		rd[2] = 1.0f - mBarColor[2];

		// Row color
		float rc[3];
		rc[0] = 1.0f - rp * rd[0];
		rc[1] = 1.0f - rp * rd[1];
		rc[2] = 1.0f - rp * rd[2];


		mCubeColor[0] = rc[0] - rc[0]*cp;
		mCubeColor[1] = rc[1] - rc[1]*cp;
		mCubeColor[2] = rc[2] - rc[2]*cp;


		// Trigger color panel select event
		mEvent.notify(mCubeColor);
	}
};