#ifndef VEE_GUIELEMENT_H
#define VEE_GUIELEMENT_H

/**
 * Basic GUI element
 */

#include "vePrerequisites.h"

#include <vector>

namespace vee {

	typedef struct Point {

		// X coordinate
		int x;

		// Y coordinate
		int y;


		//---------------------------------------------------------------
		Point() {}
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



	// GUI type
	typedef enum GUIType {

		// Default
		GUI_DEFAULT,

		// Static
		GUI_STATIC

	} GUIType;



	// GUIElement
	class GUIElement {

	public:
		GUIElement();
		virtual ~GUIElement();


	public:
		/**
		 * Mouse left button down
		 */
		virtual int mouseLDown(int x, int y);


	public:
		/**
		 * Render
		 */
		virtual void render();

		/**
		 * Init
		 */
		virtual void init();

		/**
		 * Destroy
		 */
		virtual void destroy();


	public:
		/**
		 * Add child
		 */
		void addChild(GUIElement* child);


	public:
		/**
		 * Set color
		 */
		void setColor(uchar r, uchar g, uchar b, uchar a);

		/**
		 * Set rect
		 */
		void setRect(Rect& r);


	protected:
		// GUI type
		GUIType mType;


		// Rect
		Rect mRect;


		// Color
		uchar mColor[4];


		// Parent GUI element
		GUIElement* mParent;

		// Children GUI elements
		vector<GUIElement*> mChildren;
	};
};

#endif