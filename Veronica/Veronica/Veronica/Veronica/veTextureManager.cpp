#include "veTextureManager.h"
#include "veTGALoader.h"


namespace vee {

	//---------------------------------------------------------------
	TextureManager::TextureManager() {
	}
	//---------------------------------------------------------------
	TextureManager::~TextureManager() {
		mTextures.clear();
	}

	//---------------------------------------------------------------
	// Initialize the static member
	template<> TextureManager* SingletonVee<TextureManager>::ms_Singleton = 0;
	TextureManager& TextureManager::getSingleton(void) {

		return *ms_Singleton;
	}
	//---------------------------------------------------------------
	TextureManager* TextureManager::getSingletonPtr(void) {

		return ms_Singleton;
	}

	//---------------------------------------------------------------
	// Create texture
	Texture* TextureManager::createTexture(string name) {

		Texture* texture = new Texture();
		mTextures[name] = texture;

		return texture;
	}

	//---------------------------------------------------------------
	// Load texture
	Texture* TextureManager::loadTexture(string name, const char* filename) {

		// TGA data
		TGAData tgaData;
		// Load tgaData from file
		TGALoader::loadTGAFile(&tgaData, filename);

		// Create new texture
		Texture* texture = createTexture(name);

		GLenum format, internalFormat;
		// Texture format
		switch (tgaData.mBitsPP / 8)
		{
			case 3:
				format = GL_RGB;
				internalFormat = GL_RGB8;
				break;
			case 4:
				format = GL_RGBA;
				internalFormat = GL_RGBA8;
				break;
		}

		// Initialize the texture
		texture->init(tgaData.mWidth, tgaData.mHeight,
			internalFormat, format, GL_UNSIGNED_BYTE, tgaData.mData);

		return texture;
	}

	//---------------------------------------------------------------
	// Get texture
	Texture* TextureManager::getTexture(string name) {

		map<string, Texture*>::const_iterator texture = mTextures.find(name);
		if (texture != mTextures.end()) {

			return texture->second;
		}

		return NULL;
	}

};