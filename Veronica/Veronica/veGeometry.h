#ifndef VEE_GEOMETRY_H
#define VEE_GEOMETRY_H

/**
 * Basic geometry
 */

#include "vePrerequisites.h"

namespace vee {

	/**
	 * vePoint
	 * 2D "int" point.
	 */
	typedef struct vePoint {

		// X coordinate
		int x;
		// Y coordinate
		int y;


		//---------------------------------------------------------------
		vePoint() {}
		vePoint(int px, int py) {
			x = px;
			y = py;
		}
		~vePoint() {}


		// =
		void operator = (const vePoint& p) {
			
			x = p.x;
			y = p.y;
		}

	} vePoint;



	// veRect
	typedef struct veRect {

		// X coordinate
		int x;
		// Y coordinate
		int y;
		// Width
		int w;
		// Height
		int h;


		//---------------------------------------------------------------
		veRect() {}
		veRect(int xCoord, int yCoord, int width, int height) {

			x = xCoord;
			y = yCoord;
			w = width;
			h = height;
		}
		~veRect() {}


		// =
		void operator = (const veRect& r) {

			x = r.x;
			y = r.y;
			w = r.w;
			h = r.h;
		}

	} veRect;
};

#endif