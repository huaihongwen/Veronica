#include "veFontSystem.h"

#include "veMath.h"

// Texture manager
#include "veTextureManager.h"
// Render system
#include "veRenderSystem.h"


namespace vee {

	//---------------------------------------------------------------
	FontSystem::FontSystem() {
	}

	//---------------------------------------------------------------
	FontSystem::FontSystem(const char* fontname, const char* filename) {

		// Font name
		mFontName = fontname;


		// Texture manager
		TextureManager& tm = TextureManager::getSingleton();
		
		// Load font texture from file
		Texture* tex = tm.loadTexture(mFontName, filename);


		// Font width
		mFontWidth = (int)tex->getWidth() / 16;

		// Font height
		mFontHeight = (int)tex->getHeight() / 16;


		// Font color
		mFontColor[0] = 255;
		mFontColor[1] = 0;
		mFontColor[2] = 0;
	}

	//---------------------------------------------------------------
	FontSystem::~FontSystem() {
	}


	//---------------------------------------------------------------
	// Initialize the static member.
	template<> FontSystem* SingletonVee<FontSystem>::ms_Singleton = 0;
	FontSystem& FontSystem::getSingleton(void) {

		return *ms_Singleton;
	}

	//---------------------------------------------------------------
	FontSystem* FontSystem::getSingletonPtr(void) {

		return ms_Singleton;
	}


	//---------------------------------------------------------------
	// Render
	void FontSystem::render(string& str) {

		// Prepare
		_prepare();

		// Render string
		_renderString(str);

		// End
		_end();
	}


	//---------------------------------------------------------------
	// Prepare
	void FontSystem::_prepare() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Texture manager
		TextureManager& tm = TextureManager::getSingleton();


		// Window width
		int width = rs.getWindowWidth();
		// Window height
		int height = rs.getWindowHeight();


		// Ortho projection
		rs.setOrthoProjection(0.0f, (float)width, 0.0f, (float)height);

		// Viewport
		rs.setViewport(0, 0, width, height);

		// Identity model view
		rs.identityModelView();

		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);


		// Bind font texture
		rs.bindTexture2D(tm.getTexture(mFontName)->getId(), 0);
	}

	//---------------------------------------------------------------
	// End
	void FontSystem::_end() {

		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Unbind font texture
		rs.bindTexture2D(0, 0);


		// Clear depth buffer
		rs.clearBuffers(GL_DEPTH_BUFFER_BIT);
	}


	//---------------------------------------------------------------
	// Render string
	void FontSystem::_renderString(string& str) {
	
		// Char idx
		int charIdx = 0;

		// Line idx
		int lineIdx = 0;


		// Start x
		float sX = 0.0f;

		// Start y
		float sY = 768.0f;


		// String color
		glColor3ubv(mFontColor);

		// Begin quads
		glBegin(GL_QUADS);
		// Loop each char in str
		for (uint i = 0; i < str.length(); i++) {

			// '\n'
			if (str.at(i) == 13) {

				// Reset char idx
				charIdx = 0;

				// Increase line idx
				lineIdx++;

				continue;
			} else {

				// Render char
				_renderChar(str.at(i), sX, sY, charIdx, lineIdx);

				charIdx++;
			}
		}
		glEnd();
	}


	//---------------------------------------------------------------
	// Render char
	void FontSystem::_renderChar(char c, float x, float y, int charIdx, int lineIdx) {

		
		// UV step
		float uvs = 0.0625f;


		// Find grid idx in texture
		int gridX = c % 16;
		int gridY = (int)floor((float)c / 16.0f);


		glTexCoord2f((gridX+1) * uvs, 1.0f - gridY * uvs);
		glVertex3f(x + (charIdx+1) * mFontWidth, y - lineIdx * mFontHeight, -1.0f);

		glTexCoord2f((gridX+1) * uvs, 1.0f - (gridY+1) * uvs);
		glVertex3f(x + (charIdx+1) * mFontWidth, y - (lineIdx+1) * mFontHeight, -1.0f);

		glTexCoord2f(gridX * uvs, 1.0f - (gridY+1) * uvs);
		glVertex3f(x + charIdx * mFontWidth, y - (lineIdx+1) * mFontHeight, -1.0f);

		glTexCoord2f(gridX * uvs, 1.0f - gridY * uvs);
		glVertex3f(x + charIdx * mFontWidth, y - lineIdx * mFontHeight, -1.0f);
	}
};