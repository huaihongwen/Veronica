/**
 *	Texture manager
 */

#ifndef VEE_TEXTUREMANAGER_H
#define VEE_TEXTUREMANAGER_H

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veTexture.h"

#include <map>

namespace vee {

	// Texture map
	typedef map<string, veTexture*> veTextureMap;

	// Texture manager
	class veTextureManager : public SingletonVee<veTextureManager> {

	public:
		veTextureManager();
		~veTextureManager();

		// Singleton
		static veTextureManager& getSingleton(void);
		static veTextureManager* getSingletonPtr(void);

		// Create texture
		veTexture* createTexture(string name);

		// Get texture
		veTexture* getTexture(string name);

	protected:
		// Textures
		veTextureMap mTextures;
	};
};

#endif