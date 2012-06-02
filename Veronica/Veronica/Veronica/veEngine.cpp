#include "veEngine.h"


namespace  vee {

	//---------------------------------------------------------------
	Engine::Engine() {
	}
	//---------------------------------------------------------------
	Engine::~Engine() {
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> Engine* SingletonVee<Engine>::ms_Singleton = 0;
	Engine& Engine::getSingleton(void) {
		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	Engine* Engine::getSingletonPtr(void) {
		return ms_Singleton;
	}



};