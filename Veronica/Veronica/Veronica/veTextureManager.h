#ifndef VEE_TEXTUREMANAGER_H
#define VEE_TEXTUREMANAGER_H

/* Texture manager
 */

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veTexture.h"

#include <map>

namespace vee {

	// Texture map
	typedef map<string, Texture*> TextureMap;

	// Texture manager
	class TextureManager : public SingletonVee<TextureManager> {

	public:
		TextureManager();
		~TextureManager();

		// Singleton
		static TextureManager& getSingleton(void);
		static TextureManager* getSingletonPtr(void);

		// Create texture
		Texture* createTexture(string name);

		// Load texture
		Texture* loadTexture(string name, const char* filename);

		// Get texture
		Texture* getTexture(string name);

	protected:
		// Textures
		TextureMap mTextures;
	};
};

#endif