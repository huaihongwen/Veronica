#ifndef VEE_RENDERSYSTEM_H
#define VEE_RENDERSYSTEM_H

/* Basic render system
 */

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veTransform.h"

#include <windows.h>
#include <GL\glew.h>

#include <vector>

namespace vee {

	// Simple render system
	class RenderSystem : public SingletonVee<RenderSystem> {

	public:
		RenderSystem();
		~RenderSystem();

	public:
		// Get singleton
		static RenderSystem& getSingleton(void);
		static RenderSystem* getSingletonPtr(void);

		// Set window size
		void setWindowSize(int width, int height);
		// Get window width
		int getWindowWidth();
		// Get window height
		int getWindowHeight();


		// Set viewport
		void setViewport(int x, int y, int width, int height);
		// Push viewport
		void pushViewport();
		// Pop viewport
		void popViewport();


		// Set ortho projection
		void setOrthoProjection(float l, float r, float b, float t);

		// Set perspective projection
		void setPerspectiveProjection(Transform perspective);

		// Push projection
		void pushProjection();
		// Pop projection
		void popProjection();


		// Set modelview
		void setModelView(Transform modelview);
		// Identity model view
		void identityModelView();

		// Push modelview
		void pushModelView();
		// Pop modelview
		void popModelView();


		// Clear buffer
		void clearBuffers(GLbitfield mask);

		// Draw buffers
		void drawBuffers(vector<GLenum>* buffers);


	public:
		// Textures
		// Enable texture 2d
		void enableTexture2D();
		// Diable texture 2d
		void disableTexture2D();

		// Bind texture 2d to current texture unit
		void bindTexture2D(GLuint tex, uint unit=0);


		// Bind FBO
		void bindFBO(FramebufferObject* fbo);

		// Use shader program
		void useProgram(ShaderProgram* program);

	protected:
		// Window width
		int mWindowWidth;
		// Window height
		int mWindowHeight;

		// Current fbo
		FramebufferObject* mCurFBO;

		// Current shader program
		ShaderProgram* mCurProgram;
	};
};

#endif