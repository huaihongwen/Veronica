#include "veFBOManager.h"

namespace  vee {
	
	//---------------------------------------------------------------
	FBOManager::FBOManager() {

	}
	//---------------------------------------------------------------
	FBOManager::~FBOManager() {
		mFBOs.clear();
	}


	//---------------------------------------------------------------
	// Initialize the static member
	template<> FBOManager* SingletonVee<FBOManager>::ms_Singleton = 0;
	FBOManager& FBOManager::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	FBOManager* FBOManager::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	// Create FBO
	FramebufferObject* FBOManager::createFBO(string name) {

		FramebufferObject* fbo = new FramebufferObject();
		mFBOs[name] = fbo;

		return fbo;
	}

	//---------------------------------------------------------------
	// Get FBO
	FramebufferObject* FBOManager::getFBO(string name) {

		map<string, FramebufferObject*>::const_iterator fbo = mFBOs.find(name);
		if (fbo != mFBOs.end()) {

			return fbo->second;
		}

		return NULL;
	}

};