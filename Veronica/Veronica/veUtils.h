#ifndef VEE_UTILS_H
#define VEE_UTILS_H

/*
 * veUtils.h
 */

#include "vePrerequisites.h"
#include "veMath.h"
#include "veUIComponent.h"
#include "veRenderer.h"
#include "veRenderSystem.h"

namespace vee {
	
	// Utils
	class Utils {

	public:
		//---------------------------------------------------------------
		/**
		 * This function assumes input coordinate i, j, k
		 * is inside of the volume and the "3D size" of the
		 * array is the same as volume size.
		 *
		 * Convert 3D volume coordinate into array index.
		 * @i {int} x coordinate.
		 * @j {int} y coordinate.
		 * @k {int} z coordinate.
		 * @sy {int} y size.
		 * @sz {int} z size.
		 */
		static int toArrayIndex(int i, int j, int k, int sy, int sz) {
			return i * (sy * sz) + j * sz + k;
		}


		//---------------------------------------------------------------
		/**
		 * Evenly distribute rays on a sphere
		 * @num {int} number of rays need to be generated.
		 * @result {vector<float>&} result array of rays.
		 */
		static void pointsOnSphere(int num, vector<float>& result) {

			// Inc
			float inc = MATH_PI * (3.0f - sqrt(5.0f));

			// Off
			float off = 2.0f / float(num);


			float y, r, phi;

			// Loop each ray
			for (int i = 0; i < num; i++) {

				// Y
				y = i*off - 1.0f + off*0.5f;

				// R
				r = sqrt(1.0f - y*y);

				// Phi
				phi = i*inc;


				// Push ray to result array
				result.push_back(cos(phi) * r);
				result.push_back(y);
				result.push_back(sin(phi) * r);
			}
		}


		//---------------------------------------------------------------
		/**
		 * Voxel traversal
		 * Traverse voxels by a 3d line segment and find out coordinates for
		 * intersected voxels.
		 * @x0 {float} start point x coordinate.
		 * @y0 {float} start point y coordinate.
		 * @z0 {float} start point z coordinate.
		 * @x1 {float} end point x coordinate.
		 * @y1 {float} end point y coordinate.
		 * @z1 {float} end point z coordinate.
		 * @r {vector<int>&} result array of voxel coordinates.
		 */
		static void voxelTraversal(float x0, float y0, float z0,
			float x1, float y1, float z1,
			vector<int>& r) {

			// Length
			float dx = abs(x1 - x0);
			float dy = abs(y1 - y0);
			float dz = abs(z1 - z0);


			// Start voxel coordinate
			int x = int(floor(x0));
			int y = int(floor(y0));
			int z = int(floor(z0));


			// We probably have division by zero here but IEEE 754
			// floating-point works fine.

			// Time for traversing unit length
			float dt_dx = 1.0f / dx;
			float dt_dy = 1.0f / dy;
			float dt_dz = 1.0f / dz;


			// Current time
			float t = 0.0f;


			// Number of voxel intersected
			int num = 1;


			// Increment direction
			int xInc, yInc, zInc;


			// Next intersection time x, y, z
			float xNext, yNext, zNext;


			// X direction
			if (dx == 0.0f) {

				// No increment
				xInc = 0;

				// Infinity next intersection time
				xNext = dt_dx;

			} else if (x1 > x0) {

				// Positive increment
				xInc = 1;

				// Number of intersection in x direction
				num += int(floor(x1)) - x;

				// Next intersection time
				xNext = (floor(x0) + 1.0f - x0) * dt_dx;
			
			} else {

				// Negative increment
				xInc = -1;

				// Number of intersection in x direction
				num += x - int(floor(x1));

				// Next intersection time
				xNext = (x0 - floor(x0)) * dt_dx;
			}


			// Y direction
			if (dy == 0.0f) {

				// No increment
				yInc = 0;

				// Infinity next intersection time
				yNext = dt_dy;

			} else if (y1 > y0) {

				// Positive increment
				yInc = 1;

				// Number of intersection in y direction
				num += int(floor(y1)) - y;

				// Next intersection time
				yNext = (floor(y0) + 1.0f - y0) * dt_dy;

			} else {

				// Negative increment
				yInc = -1;

				// Number of intersection in y direction
				num += y - int(floor(y1));

				// Next intersection time
				yNext = (y0 - floor(y0)) * dt_dy;
			}


			// Z direction
			if (dz == 0.0f) {

				// No increment
				zInc = 0;

				// Infinity next intersection time
				zNext = dt_dz;

			} else if (z1 > z0) {

				// Positive increment
				zInc = 1;

				// Number of intersection in z direction
				num += int(floor(z1)) - z;

				// Next intersection time
				zNext = (floor(z0) + 1.0f - z0) * dt_dz;

			} else {

				// Negative increment
				zInc = -1;

				// Number of intersection in z direction
				num += z - int(floor(z1));

				// Next intersection time
				zNext = (z0 - floor(z0)) * dt_dz;
			}



			// Loop each intersection
			for (; num > 0; --num) {

				// Mark current intersection coordinate
				r.push_back(x);
				r.push_back(y);
				r.push_back(z);


				// Find the smallest next intersection time
				if (xNext < yNext && xNext < zNext) {

					// Step x
					x += xInc;

					// Current time
					t = xNext;

					// Next intersection x
					xNext += dt_dx;

				} else if (yNext < zNext) {

					// Step y
					y += yInc;

					// Current time
					t = yNext;

					// Next intersection y
					yNext += dt_dy;

				} else {

					// Step z
					z += zInc;

					// Current time
					t = zNext;

					// Next intersection z
					zNext += dt_dz;
				}
			}
		}



		//---------------------------------------------------------------
		/**
		 * Unproject 3d window space coordinate to 3d world space coordinate.
		 * @wx {int} x coordinate relative to window's top-left corner.
		 * @wy {int} y coordinate relative to window's top-left corner.
		 * @wz {float} window space depth, 0.0f to 1.0f.
		 * @result {float*} 3d world space coordinate.
		 * @return {bool} unproject succeed or not.
		 */
		static bool unProject(int wx, int wy, float wz, float* result) {

			// Render system
			RenderSystem& rs = RenderSystem::getSingleton();

			// Renderer
			Renderer& renderer = Renderer::getSingleton();


			// Window width
			int ww = rs.getWindowWidth();
			// Window height
			int wh = rs.getWindowHeight();


			// Viewport data
			int vpData[4];
			renderer.getViewport(vpData);

			// View data
			float vData[16];
			renderer.getView(vData);

			// Projection data
			float pData[16];
			renderer.getProjection(pData);


			// View, projection matrix
			Transform vMat, pMat;

			vMat.setValue(vData);
			pMat.setValue(pData);

			//	VP inverse matrix
			Transform vpInv = pMat * vMat;

			// Can't invert vp
			if (!vpInv.invert()) {
				return false;
			}


			// x, y inside viewport
			float x = (float)(wx - vpData[0]);
			// Reverse to OpenGL y direction
			float y = (float)(wh - wy - vpData[1]);


			// NDC coordinates
			Vector4 ndc;

			// Map back to -1.0 - 1.0
			ndc.setValue(x / vpData[2] * 2.0f - 1.0f, y / vpData[3] * 2.0f - 1.0f, wz * 2.0f - 1.0f, 1.0f);


			// Calculate world space coordinates (non-homogeneous)
			Vector4 world = vpInv * ndc;

			// Back to homogeneous
			if (world[3] == 0) {

				return false;
			}
			world /= world[3];


			// Output result
			result[0] = world[0];
			result[1] = world[1];
			result[2] = world[2];

			return true;
		}


		//---------------------------------------------------------------
		/**
		 * Point in rect
		 * @p {Point&} input point.
		 * @r {Rect&} input rect.
		 * @return {bool} inside or not.
		 */
		static bool pointInRect(vePoint& p, veRect& r) {

			if ( p.x >= r.x && p.x <= (r.x+r.w) && p.y >= r.y && p.y <= (r.y+r.h)) {
				return true;
			}

			return false;
		}


		//---------------------------------------------------------------
		/**
		 * Get voxel face texture coordinates.
		 * @t {VoxelType} voxel type.
		 * @fIdx {int} face index.
		 * @coords {float*} result texture coordinates.
		 */
		static void getVoxelFaceTexCoords(VoxelType t, int fIdx, float* coords) {

			// Step
			float step = 1.0f / 16.0f;

			// Tile x, tile y
			int tx, ty;


			// Voxel type
			switch (t) {

			case VT_PURPLE_BRICK:
				{
					tx = 0;
					ty = 1;
				}
				break;

			case VT_YELLOW_BRICK:
				{
					if (fIdx == 4 || fIdx == 5) {
						tx = 0;
						ty = 2;
					} else {
						tx = 0;
						ty = 3;
					}
				}
				break;

			case VT_GREY_BRICK_1:
				{
					tx = 5;
					ty = 15;
				}
				break;

			case VT_GREY_BRICK_2:
				{
					tx = 6;
					ty = 12;
				}
				break;

			case VT_GREY_BRICK_3:
				{
					tx = 4;
					ty = 9;
				}
				break;

			case VT_GREY_BRICK_4:
				{
					tx = 5;
					ty = 9;
				}
				break;

			case VT_GREY_BRICK_5:
				{
					tx = 13;
					ty = 9;
				}
				break;

			case VT_GREY_BRICK_6:
				{
					tx = 14;
					ty = 9;
				}
				break;

			case VT_GREY_BRICK_7:
				{
					tx = 1;
					ty = 15;
				}
				break;

			case VT_GREY_BRICK_8:
				{
					tx = 0;
					ty = 14;
				}
				break;

			case VT_GREY_BRICK_9:
				{
					tx = 6;
					ty = 15;
				}
				break;


			case VT_GREY_METAL:
				{
					tx = 1;
					ty = 1;
				}
				break;

			case VT_GREENBLUE_METAL:
				{
					tx = 1;
					ty = 2;
				}
				break;

			case VT_DARKPURPLE_METAL:
				{
					tx = 1;
					ty = 3;
				}
				break;

			case VT_DARKBLUE_METAL:
				{
					tx = 1;
					ty = 4;
				}
				break;

			case VT_BROWN_METAL:
				{
					tx = 1;
					ty = 5;
				}
				break;

			case VT_DARKGREEN_METAL:
				{
					tx = 1;
					ty = 6;
				}
				break;

			case VT_DARKRED_METAL:
				{
					tx = 1;
					ty = 7;
				}
				break;

			case VT_BLACK_METAL:
				{
					tx = 1;
					ty = 8;
				}
				break;


			case VT_DARK_LIGHT:
				{
					tx = 3;
					ty = 2;
				}
				break;

			case VT_BRIGHT_LIGHT:
				{
					tx = 4;
					ty = 2;
				}
				break;


			default:
				{
					tx = 0;
					ty = 0;
				}
				break;
			}


			// Output
			coords[0] = tx*step;
			coords[1] = ty*step + step;
			coords[2] = tx*step;
			coords[3] = ty*step;
			coords[4] = tx*step + step;
			coords[5] = ty*step;
			coords[6] = tx*step + step;
			coords[7] = ty*step + step;
		}
	};
};

#endif