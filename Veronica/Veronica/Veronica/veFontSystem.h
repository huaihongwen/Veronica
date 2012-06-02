#ifndef VEE_FONTSYSTEM_H
#define VEE_FONTSYSTEM_H


/*
 * Font system
 */


#include "vePrerequisites.h"
#include "veSingleton.h"


namespace vee {

	// Font system
	class FontSystem : public SingletonVee<FontSystem> {

	public:
		FontSystem();
		FontSystem(const char* fontname, const char* filename);
		~FontSystem();

	public:
		// Get singleton
		static FontSystem& FontSystem::getSingleton(void);
		// Get singleton ptr
		static FontSystem* FontSystem::getSingletonPtr(void);


	public:
		// Render
		void render(string& str);


	protected:
		// Prepare
		void _prepare();

		// End
		void _end();


		// Render string
		void _renderString(string& str);

		// Render char
		void _renderChar(char c, float x, float y, int charIdx, int lineIdx);

	protected:
		// Font width
		int mFontWidth;
		
		// Font height
		int mFontHeight;

		// Font color
		uchar mFontColor[3];


		// Font name
		string mFontName;
	};
};

#endif