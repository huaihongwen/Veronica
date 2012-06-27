#ifndef VEE_LIGHTINGCALCULATOR_H
#define VEE_LIGHTINGCALCULATOR_H

/**
 * veLightingCalculator.h
 */

#include "vePrerequisites.h"
#include "veScene.h"

namespace vee {

	/**
	 * Lighting calculator
	 */
	class LightingCalculator {

	public:
		LightingCalculator();
		~LightingCalculator();


	public:
		/**
		 * Init
		 */
		void init(int sx, int sy, int sz);

		/**
		 * Destroy
		 */
		void destroy();


	public:
		/**
		 * Set scene
		 */
		void setScene(Scene* s);


	protected:
		// Pointer to scene
		Scene* mScene;


		// Sky light data
		float* mSkyLightData;
	};
};


#endif