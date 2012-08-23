#include "veTextureManager.h"

namespace vee {
	// Constructor
	veTextureManager::veTextureManager() {}

	// Constructor
	veTextureManager::~veTextureManager() {
		mTextures.clear();
	}

	// Initialize the static member
	template<> veTextureManager* SingletonVee<veTextureManager>::ms_Singleton = 0;
	veTextureManager& veTextureManager::getSingleton(void) {

		return *ms_Singleton;
	}

	veTextureManager* veTextureManager::getSingletonPtr(void) {

		return ms_Singleton;
	}

	// Create a new texture and add it to the map
	veTexture* veTextureManager::createTexture(string name) {

		veTexture* texture = new veTexture();
		mTextures[name] = texture;

		return texture;
	}

	// Get texture by name
	veTexture* veTextureManager::getTexture(string name) {

		map<string, veTexture*>::const_iterator texture = mTextures.find(name);
		if (texture != mTextures.end()) {

			return texture->second;
		}

		return NULL;
	}

};