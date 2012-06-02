#ifndef VEE_UTILS_H
#define VEE_UTILS_H

/*
 * veUtils.h
 */

#include "vePrerequisites.h"
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
	};
};

#endif