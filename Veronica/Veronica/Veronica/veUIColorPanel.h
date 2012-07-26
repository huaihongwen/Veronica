#ifndef VEE_UICOLORPANEL_H
#define VEE_UICOLORPANEL_H

/**
 * veUIColorPanel.h
 */

#include "vePrerequisites.h"
#include "veUIComponent.h"
#include "veEvent.h"

namespace vee {

	/**
	 * Color panel
	 */
	class UIColorPanel : public UIComponent {

	public:
		UIColorPanel();
		~UIColorPanel();


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
		 * Render
		 */
		void render();


	public:
		/**
		 * Mouse left button up
		 */
		bool mouseLUp(int x, int y);


	protected:
		/**
		 * Render bar
		 */
		void _renderBar();

		/**
		 * Render cube
		 */
		void _renderCube();


		/**
		 * Select color
		 */
		void _selectColor(int x, int y);


		/**
		 * Calculates bar color
		 */
		void _calculateBarColor();

		/**
		 * Calculates cube color
		 */
		void _calculateCubeColor();


	protected:
		// Bar rect
		Rect mBarRect;

		// Cube rect
		Rect mCubeRect;


		// Bar color
		float mBarColor[3];

		// Cube color
		float mCubeColor[3];


		// Bar indicator pos y
		int mBarIndicator;


		// Cube indicator pos x
		int mCubeIndicatorX;
		// Cube indicator pos y
		int mCubeIndicatorY;


	public:
		// Event
		Event1<bool, float*> mEvent;
	};
};

#endif