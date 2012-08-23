#ifndef VEE_COLOR_H
#define VEE_COLOR_H

#include "vePrerequisites.h"

namespace vee {

	// A basic color class, supports 4 color channels rgba,
	// this can be extended to support float and int color channel??
	class veColor {
	
	public:
		// Constructor
		veColor() {}
		// Copy constructor
		veColor(veColor& color) {
			mRGBA[0] = color.mRGBA[0];
			mRGBA[1] = color.mRGBA[1];
			mRGBA[2] = color.mRGBA[2];
			mRGBA[3] = color.mRGBA[3];
		}
		// Destructor
		~veColor() {}

	public:
		// Initializes the color channels
		// @params
		// @return
		void init() {
			mRGBA[0] = 0;
			mRGBA[1] = 0;
			mRGBA[2] = 0;
			mRGBA[3] = 255;
		}

		// Overloads operator [] to better access each color channel, this function doesnt
		// modify the value of any member variable
		// @params
		// idx (const int&)			Ref to an integer idx, range from 0 to 3
		// @return
		// (uchar)					Returns the value of corresponding channel value
		uchar operator [] (const int& idx) const {
			return mRGBA[idx];
		}

		// Sets the color using 3 color channels
		// @params
		// r, g, b (uchar)		RGBA channel values
		// @return
		void set(uchar r, uchar g, uchar b) {
			mRGBA[0] = r;
			mRGBA[1] = g;
			mRGBA[2] = b;
		}

		// Sets the color using 4 color channels
		// @params
		// r, g, b, a (uchar)		RGBA channel values
		// @return
		void set(uchar r, uchar g, uchar b, uchar a) {
			mRGBA[0] = r;
			mRGBA[1] = g;
			mRGBA[2] = b;
			mRGBA[3] = a;
		}

		// Sets the color using another color
		// @params
		// color (veColor&)			Ref to another color
		// @return
		void set(const veColor& color) {
			mRGBA[0] = color[0];
			mRGBA[1] = color[1];
			mRGBA[2] = color[2];
			mRGBA[3] = color[3];
		}

		// Gets the pointer to the color channel array
		// @params
		// @return
		// (uchar*)					Returns the pointer to the color channel array
		uchar* get() {
			return mRGBA;
		}

	protected:
		uchar	mRGBA[4];
	};
};

#endif