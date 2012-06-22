#ifndef VEE_UICOMPONENT_H
#define VEE_UICOMPONENT_H

/**
 * Basic UI component
 */

#include "vePrerequisites.h"
#include "veTexture.h"

namespace vee {

	/**
	 * Point
	 * 2D "int" point.
	 */
	typedef struct Point {

		// X coordinate
		int x;
		// Y coordinate
		int y;


		//---------------------------------------------------------------
		Point() {}
		Point(int px, int py) {
			x = px;
			y = py;
		}
		~Point() {}


		// =
		void operator = (const Point& p) {
			
			x = p.x;
			y = p.y;
		}

	} Point;



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



	/**
	 * UI component
	 */
	class UIComponent {

	public:
		UIComponent();
		~UIComponent();


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
		 */
		virtual void render();


	public:
		/**
		 * Mouse left button up
		 */
		virtual void mouseLUp(int x, int y);


	public:
		/**
		 * Set rect
		 */
		void setRect(Rect& r);

		/**
		 * Set background color
		 */
		void setBackgroundColor(uchar r, uchar g, uchar b);



	protected:
		// Rect
		Rect mRect;


		// Background color
		uchar mColor[3];


		// Texture
		Texture* mTexture;

		// Texture coordinates
		float mTexCoords[8];
	};
};

#endif