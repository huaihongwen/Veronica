#ifndef VEE_LIGHTINGENGINE_H
#define VEE_LIGHTINGENGINE_H

/**
 * veLightingEngine.h
 */

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veScene.h"

namespace vee {

	/**
	 * LightingEngine
	 */
	class LightingEngine : public SingletonVee<LightingEngine> {
	
	public:
		LightingEngine();
		~LightingEngine();


	public:
		static LightingEngine& getSingleton(void);
		static LightingEngine* getSingletonPtr(void);


	public:
		/**
		 * Init
		 */
		void init(Scene* scene);

		/**
		 * Destroy
		 */
		void destroy();


	protected:
		// Scene
		Scene* mScene;


		// Sun light
		float* mSunLightData;
	}
};


#endif