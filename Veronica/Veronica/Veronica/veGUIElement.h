#ifndef VEE_GUIELEMENT_H
#define VEE_GUIELEMENT_H

/**
 * Basic GUI element
 */

#include "vePrerequisites.h"

namespace vee {

	// Rect
	typedef struct Rect {

		// X coordinate
		int x;
		
		// Y coordinate
		int y;

		// Width
		int w;

		// Height
		int h;


		//---------------------------------------------------------------
		Rect() {}
		Rect(int xCoord, int yCoord, int width, int height) {

			x = xCoord;
			y = yCoord;
			w = width;
			h = height;
		}
		~Rect() {}


		// =
		void operator = (const Rect& r) {

			x = r.x;
			y = r.y;
			w = r.w;
			h = r.h;
		}

	} Rect;



	// GUIElement
	class GUIElement {

	public:
		GUIElement();
		virtual ~GUIElement();


	public:
		/**
		 * Render
		 */
		virtual void render();

		/**
		 * Destroy
		 */
		virtual void destroy();


	public:
		/**
		 * Set color
		 */
		void setColor(uchar* color);
		/**
		 * Set color
		 */
		void setColor(uchar r, uchar g, uchar b, uchar a);

		/**
		 * Get rect
		 */
		Rect& getRect();

		/**
		 * Set rect
		 */
		void setRect(Rect& r);


	protected:
		// Rect
		Rect mRect;

		// Color
		uchar mColor[4];
	};
};

#endif