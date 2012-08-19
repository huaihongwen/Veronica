#ifndef VEE_ENGINE_H
#define VEE_ENGINE_H


/*
 * veEngine.h
 */


#include "vePrerequisites.h"
// Singleton
#include "veSingleton.h"

// Texture manager
#include "veTextureManager.h"
// FBO manager
#include "veFBOManager.h"
// GLSL manager
#include "veGLSLManager.h"

// Render system
#include "veRenderSystem.h"
// Renderer
#include "veRenderer.h"



namespace vee {

	// Engine
	class Engine : public SingletonVee<Engine> {

	public:
		Engine();
		~Engine();

	public:
		// Get singleton
		Engine& getSingleton(void);
		Engine* getSingletonPtr(void);


	protected:
		// Texture manager
		veTextureManager* mTextureManager;
		// FBO manager
		FBOManager* mFBOManager;
		// GLSL manager
		GLSLManager* mGLSLManager;

		// Render system
		RenderSystem* mRenderSystem;
		// Renderer
		Renderer* mRenderer;
	};
};

#endif