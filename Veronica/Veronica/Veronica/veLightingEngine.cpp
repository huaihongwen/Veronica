#include "veLightingEngine.h"

namespace vee {

	//---------------------------------------------------------------
	LightingEngine::LightingEngine() {
	}

	//---------------------------------------------------------------
	LightingEngine::~LightingEngine() {

		// Destroy
		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> LightingEngine* SingletonVee<LightingEngine>::ms_Singleton = 0;
	LightingEngine& LightingEngine::getSingleton(void) {
		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	LightingEngine* LightingEngine::getSingletonPtr(void) {
		return ms_Singleton;
	}


	//---------------------------------------------------------------
	/**
	 * Init
	 */
	void LightingEngine::init() {
	}

	//---------------------------------------------------------------
	/**
	 * Destroy
	 */
	void LightingEngine::destroy() {
	}
}