#ifndef VEE_UICOMPONENT_H
#define VEE_UICOMPONENT_H

/**
 * Basic UI component
 */

#include "vePrerequisites.h"
#include "veGeometry.h"
#include "veTexture.h"

namespace vee {

	/**
	 * UI component
	 */
	class veUIComponent {

	public:
		veUIComponent();
		~veUIComponent();

	public:

		/**
		 * Init
		 */
		virtual void init();

		/**
		 * Destroy
		 */
		virtual void destroy();

		/**
		 * Render
		 * This function assumes the ortho projection and viewport are
		 * already setup.
		 */
		virtual void render();

	public:
		/**
		 * Mouse left button up
		 */
		virtual bool mouseLUp(int x, int y);

		/**
		 * Mouse left button down
		 */
		virtual bool mouseLDown(int x, int y);


	public:
		// Get the UI's rect
		// @params
		// @return
		// (veRect&)			// Returns the rect's reference
		veRect& getRect();

		/**
		 * Set rect
		 */
		void setRect(veRect& r);

		/**
		 * Set background color
		 */
		void setBackgroundColor(uchar r, uchar g, uchar b);

		/**
		 * Set texture
		 */
		void setTexture(veTexture* tex);

		/**
		 * Set texture coordinates
		 */
		void setTexCoords(float* coords);

	protected:
		// Flag to tell whether this UI component is being selected or not
		bool mIsSelected;

		// The width of the borders of this UI, the borders would be drawn only
		// if its selected.
		// TODO: this could just be some kind of UI config enumerations value, so
		// each UI component doesnt need to keep its own copy
		int mBorderWidth;

		// Rect contains the start pos, width and height of this UI
		veRect _mRect;

		// Background color
		uchar mBgColor[3];

		// Pointer to the UI's texture object
		veTexture* mTexture;

		// Texture coordinates
		float mTexCoords[8];
	};
};

#endif