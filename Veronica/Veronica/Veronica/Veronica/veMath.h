#ifndef VEE_MATH_H
#define VEE_MATH_H

/*
 * veMath.h
 * This file contains all math stuffs for the engine
 */

#include "vePrerequisites.h"
#include <math.h>

namespace vee {

	// Constants
	#define MATH_PI 3.14159265f
	#define MATH_HALF_PI 1.580796325f
	#define MATH_2_PI 6.2831853f


	//---------------------------------------------------------------
	// Random from -1.0f to 1.0f
	static float randomNoise(int x, int y, int z, int seed) {

		// Different seed give different random functions
		int n = seed + x*73 + y*179 + z*283;

		n = (n << 13) ^ n;

		int m = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		
		// Return -1.0f to 1.0f
		return 1.0f - ((float)m / 1073741824.0f);
	}

	//---------------------------------------------------------------
	// Linear interpolation
	static float lerp(float a, float b, float t) {

		return a * (1 - t) + t * b;
	}

	//---------------------------------------------------------------
	// Cosine interpolation
	static float coerp(float a, float b, float t) {

		float ft = t * 3.1415927f;

		float f = (1.0f - (float)cos(ft)) * 0.5f;
		
		return a * (1.0f - f) + b * f;
	}
};

#endif