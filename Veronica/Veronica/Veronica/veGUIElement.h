#ifndef VEE_GUIELEMENT_H
#define VEE_GUIELEMENT_H

/**
 * Basic GUI element
 */

#include "vePrerequisites.h"

#include <vector>

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

		// Simple
		GUI_SIMPLE,

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
		 * Add child
		 */
		void addChild(GUIElement* child);

		/**
		 * Remove child
		 */
		void removeChild(GUIElement* child);

		/**
		 * Get child by type
		 */
		GUIElement* getChildByType(GUIType type);


	public:
		/**
		 * Set background color
		 */
		void setBackgroundColor(uchar r, uchar g, uchar b, uchar a);

		/**
		 * Set border color
		 */
		void setBorderColor(uchar r, uchar g, uchar b, uchar a);

		/**
		 * Set rect
		 */
		void setRect(Rect& r);

		/**
		 * Get type
		 */
		GUIType getType();


	protected:
		// GUI type
		GUIType mType;


		// Rect
		Rect mRect;


		// Background color
		uchar mBackgroundColor[4];

		// Border color
		uchar mBorderColor[4];


		// Parent
		GUIElement* mParent;

		// Children
		vector<GUIElement*> mChildren;
	};
};

#endif